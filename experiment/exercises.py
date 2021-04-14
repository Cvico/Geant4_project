import os, re, sys
import ROOT as r
import numpy as np
from copy import deepcopy
import argparse
import plotter as g4plt
env_variables = { "matching" : "(.*):(.*);(.*),(.*)" }

def add_options():
    parser = argparse.ArgumentParser(description='Geant4 simulation plotter')
    parser.add_argument('--exercise', '-e', metavar = 'exercise', help = 'Exercise from the report that we want to reproduce')
  
    env_variables["exercise"] = parser.parse_args().exercise
    return 

def create_histos():
    # Read the txt file containing this information
    txt_name = "./experiment/g4plots.txt"
    f = open(txt_name)
    lines = [ re.match(env_variables["matching"], line.replace(" ", "")).groups() for line in f.readlines() if ("#" not in line[0] and line!="" and line!="\n") ]
    hists_to_fill = {}
    for line in lines:
	processed_line = line[1].replace("[", "").replace("]", "").split(",") 
	nbins = int(processed_line[0])
	xlow  = float(processed_line[1])
	xup   = float(processed_line[2])
	hists_to_fill[line[0]] = r.TH1D(line[0],"", nbins, xlow, xup)
    f.close()
    env_variables["hists_to_fill"] = hists_to_fill
    return 

def fill_histos(var):
    histos  = env_variables["histograms"]
    samples = env_variables["histograms"].keys()
    env_variables["ret_histograms"] = {}

    for index, s in enumerate(samples):

        forCopy = deepcopy(env_variables["hists_to_fill"][var].Clone("%s_%s_toFill"%(var, s)))
        h = histos[s][var] if s != "Meroli" else histos[s]
	
	if s == "Meroli": # This is a special case
		env_variables["ret_histograms"][s] = deepcopy(h.Clone("%s_%s"%(var, s)))
		continue

	for bini in range(1, h.GetNbinsX()+1):
 		forCopy.SetBinContent(bini, 0)
		forCopy.Fill(h.GetBinCenter(bini), h.GetBinContent(bini))

	# Store a copy
	env_variables["ret_histograms"][s] = deepcopy(forCopy.Clone("%s_%s"%(var, s)))
	del forCopy

    return

def run_exercise(exercise):
    # === First of all, read the txt which has the information about the histograms that will be filled
    create_histos()

    if exercise == "1":
	env_variables["path"] = "./experiment/inputs/ex1/"
	env_variables["outpath"] = "./experiment/results/ex1/"
	
    list_rfiles = [ "/".join([env_variables["path"], rfile]) for rfile in os.listdir(env_variables["path"]) if (".root" in rfile) == True ]
    set_histograms_dict( list_rfiles if len(list_rfiles) != 1 else list_rfiles[0] )
    env_variables["histograms"]["Meroli"] = get_histo_meroli() if exercise == "1" else None

    fill_histos("Edep")
    return 

def get_histo_meroli():
  
   # Read the .dat file from data and simulation
   data = open("./Meroli/exp_Meroli_100MeV_electron_5p6um_Si.dat")
   sim = open("./Meroli/Hist_Edep.dat")
  
   data_bins = [(float(line.split(" ")[0]), float(line.split(" ")[1].split("\n")[0])) for line in data.readlines() if "#" not in line[0] ]
    
   x_bins_data = [el[0]/1000 for el in data_bins]
   x_bins_data = np.asarray(x_bins_data)
   
   y_bins_data = [el[1] for el in data_bins]
   y_bins_data = np.asarray(y_bins_data)
   
   h_data  = r.TH1D("data_meroli", "", len(x_bins_data)-1, x_bins_data)
   
   for bini in range(len(x_bins_data)):
	h_data.Fill(x_bins_data[bini], y_bins_data[bini])
  
   data.close()
   sim.close()
   return h_data


def get_histograms(rfile):
    
    f = r.TFile.Open(rfile)
    histos = f.Get("histograms")
    ret_histos = { key.GetName() : #hist_name  
         deepcopy(histos.Get(key.GetName())) for key in histos.GetListOfKeys() }
    f.Close()
    del f
    return ret_histos

def set_histograms_dict(rfiles):
    ''' 
    Function to store histograms from rootfiles in a 
    custom environmental variable
    '''
    if isinstance(rfiles, list):	
	h_dict = { re.match("^(.*)/(.*).root$", rfile).groups()[1] : get_histograms(rfile) for rfile in rfiles }
    else:
	h_dict = {rfiles.split(".root")[0].split(env_variables["path"])[1].split("/")[1] : get_histograms(rfiles)}

    env_variables["histograms"] = h_dict
    return 


# === Main script
if __name__ == "__main__": 
    add_options()
 
    run_exercise(env_variables["exercise"])

    g4plt.draw_histos(env_variables)

    os.system("cp -r ./experiment/results/ex1 ~/www/private/FPFE/")

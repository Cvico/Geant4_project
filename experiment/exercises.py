import os, re, sys
import ROOT as r
import numpy as np
from copy import deepcopy
import argparse
import plotter as g4plt
env_variables = { "matching" : "(.*):(.*);(.*),(.*)" }




def fit_meroli(fitType):

    mer = env_variables["histograms"]["Meroli"]
    xmin, xmax = mer.GetXaxis().GetXmin(), mer.GetXaxis().GetXmax() 
    p0_init = max(mer.GetY())/2.0
    
    if fitType == "convolved":
       nPars = 5

       p1_init = 0.9
       p2_init = 0.3
       p3_init = 2.56 
       p4_init = 1.0 
       
       fitFCN_conv = r.TF1Convolution("landau", "gausn", xmin, xmax, True)
       fitFCN_conv.SetRange(xmin, xmax)
       fitFCN_conv.SetNofPointsFFT(1000)
       fitFCN = r.TF1(fitType, fitFCN_conv, xmin, xmax, fitFCN_conv.GetNpar())
       fitFCN.SetParameters(p0_init, p1_init, p2_init, p3_init, p4_init)
     
    if fitType == "landau":   
       nPars = 3
       p1_init = 2.56 
       p2_init = 1.0
       fitFCN = r.TF1(fitType, fitType, xmin, xmax) 
       fitFCN.SetParameters(p0_init, p1_init, p2_init)
       fitFCN.SetLineColor(r.kTeal+5)
    if fitType == "gausn":
       nPars = 3
       p1_init = 1.0
       p2_init = 0.0
       fitFCN = r.TF1(fitType, fitType, xmin, xmax) 
       fitFCN.SetParameters(p0_init, p1_init, p2_init)

    fitResult = mer.Fit(fitType, "BS+", "", xmin, xmax )

    fits = [mer.GetFunction(fitType).GetParameter(i) for i in range(0, nPars)]
    return (fitFCN, fits)

def run_exercise(exercise):
    # === First of all, read the txt which has the information about the histograms that will be filled
    env_variables["histograms"] = {}
    env_variables["fitFuncs"] = {}
    env_variables["path"] = "./experiment/inputs/ex%s/"%exercise
    env_variables["outpath"] = "./experiment/results/ex%s/"%exercise

       
    list_rfiles = [ "/".join([env_variables["path"], rfile]) for rfile in os.listdir(env_variables["path"]) if (".root" in rfile) == True ]
    set_histograms_dict( list_rfiles if len(list_rfiles) != 1 else list_rfiles[0] )
    
    if exercise == "1":
	env_variables["histograms"]["Meroli"] = get_histo_meroli() 	
        env_variables["fitFuncs"]["Landau"] = fit_meroli("landau")
	#env_variables["fitFuncs"]["Gaussn"] = fit_meroli("gausn")
	env_variables["fitFuncs"]["convolved"] = fit_meroli("convolved")

    if exercise == "3":
       env_variables["ret_histograms"] = normalize_x_axis()
    return 
def normalize_x_axis():
    histos = env_variables["histograms"]
    ret = {}
    samples = histos.keys()
    for s in samples:
        E0 = float(re.match("(.*)_(.*)", s).groups()[1][:-3])
        part = re.match("(.*)_(.*)", s).groups()[0]
        ret[s] = {}
        hs = histos[s]
        for histo in ["Eecal", "Ehcal"]:
            h = hs[histo]
            hret = r.TH1D(h.GetName()+"_%s_%3.3f_normalizedXaxis"%(part,E0), "", h.GetNbinsX(), 0, 1 )
            for bini in range(1, h.GetNbinsX()+1):
                hret.Fill(h.GetBinCenter(bini)/E0, h.GetBinContent(bini))
            ret[s][histo] = hret

    return ret

def get_histo_meroli():
  
   # Read the .dat file from data and simulation
   data = open("./Meroli/exp_Meroli_100MeV_electron_5p6um_Si.dat")
   sim = open("./Meroli/Hist_Edep.dat")
  
   data_bins = [(float(line.split(" ")[0]), float(line.split(" ")[1].split("\n")[0])) for line in data.readlines() if "#" not in line[0] ]
    
   x_bins_data = [el[0] for el in data_bins]
   x_bins_data = np.asarray(x_bins_data)
   
   y_bins_data = [el[1] for el in data_bins]
   y_bins_data = np.asarray(y_bins_data)
   
   gr_data = r.TGraph(len(x_bins_data)) 
   for bini in range(len(x_bins_data)):
	gr_data.SetPoint(bini, x_bins_data[bini], y_bins_data[bini])
  
   data.close()
   sim.close()
   return gr_data 


def get_histograms(rfile):
    
    f = r.TFile.Open(rfile)
    
    if env_variables["exercise"] == "3": # different tree structure for exercise3
        ret_histos = {key.GetName() : #hist_name  
                      deepcopy(f.Get(key.GetName())) for key in f.GetListOfKeys() if key.GetName() != "B4"}
    else:
        histos = f.Get("histograms")
        ret_histos = { key.GetName() : #hist_name  
                       deepcopy(histos.Get(key.GetName())) for key in histos.GetListOfKeys() }
    f.Close()
    return ret_histos

def set_histograms_dict(rfiles):
    ''' 
    Function to store histograms from rootfiles in a 
    custom environmental variable
    '''
    if isinstance(rfiles, list):	
	for rfile in rfiles:
	   filename =  re.match("^(.*)/(.*).root$", rfile).groups()[1]
	   env_variables["histograms"][ filename ] = get_histograms(rfile)

    else:
	filename = rfiles.split(".root")[0].split(env_variables["path"])[1].split("/")[1] 
	env_variables["histograms"][ filename ] = get_histograms(rfiles)

    return 


# === Main script
if __name__ == "__main__": 

    exercise = sys.argv[1]
    env_variables["exercise"] = str(exercise)
    run_exercise(env_variables["exercise"])

    g4plt.draw_histos(env_variables)

#    os.system("cp -r ./experiment/results/ex%s/* ~/www/private/FPFE/"%env_variables["exercise"])



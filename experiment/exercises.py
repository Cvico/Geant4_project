import os, re, sys
import ROOT as r
from copy import deepcopy
import argparse
import plotter as g4plt
env_variables = { "matching" : "(.*):(.*);(.*),(.*)" }

def add_options():
    parser = argparse.ArgumentParser(description='Geant4 simulation plotter')
    parser.add_argument('--exercise', '-e', metavar = 'exercise', help = 'Exercise from the report that we want to reproduce')
  
    env_variables["exercise"] = parser.parse_args().exercise
    return 

def set_exercise_config(exercise):
    if exercise == "1":
	env_variables["path"] = "./experiment/inputs/ex1/"
	env_variables["outpath"] = "./experiment/results/ex1/"
    return 

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
    h_dict = { re.match("^(.*)/(.*).root$", rfile).groups()[1] : get_histograms(rfile) for rfile in rfiles }
    files = list(h_dict.keys())
    
    env_variables["AnalysedFiles"] = files
    env_variables["histograms"] = h_dict
    return 


# === Main script
if __name__ == "__main__": 
    add_options()
    set_exercise_config(env_variables["exercise"])    
    # Get a list of all the rootfiles in the given path
    list_rfiles = [ "/".join([env_variables["path"], rfile]) for rfile in os.listdir(env_variables["path"]) if (".root" in rfile) == True ]
    
    # Get a dictionary with the histograms contained in the rootfiles
    set_histograms_dict( list_rfiles if len(list_rfiles) != 1 else list_rfiles[0] )
    
    # Print the histograms following the txt directives.
    g4plt.draw_histos(env_variables)

    os.system("cp -r ./experiment/results/ex1 ~/www/private/FPFE/")

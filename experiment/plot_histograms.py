# ========
# Main imports
# =========

import ROOT as r 
import numpy as np
import argparse
import os, sys, re
from copy import deepcopy

def add_options():
    parser = argparse.ArgumentParser(description='Geant4 simulation plotter')
    parser.add_argument('--path', '-p', metavar = 'path', help = 'path where the rootfile(s) is(are) stored')
    return parser


def get_histograms(rfile):
    f = r.TFile.Open(rfile)
    f.ls()
    f.Close()
    del f
    
def get_histograms_dict(rfiles):
    if isinstance(rfiles, str):
        print("no list, just words")
        return get_histograms(rfiles)
    h_dict = { get_histograms(rfile) for rfile in rfiles }
        
    return h_dict

# === Main script
if __name__ == "__main__": 
    options = add_options().parse_args()
    
    # unpack options
    path = options.path
    # Get a list of all the rootfiles in the given path
    list_rfiles = [ "/".join([path, rfile]) for rfile in os.listdir(path) if (".root" in rfile) == True ]
    
    # Get a dictionary with the histograms contained in the rootfiles
    histograms = get_histograms_dict(list_rfiles if len(list_rfiles) != 1 else list_rfiles[0])
        
    
    

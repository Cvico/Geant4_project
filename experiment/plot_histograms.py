# ================== #
#    Main imports    #
# ================== #



import ROOT as r 
import numpy as np
import argparse
import os, sys, re
from copy import deepcopy

r.gROOT.SetBatch(1)
env_variables = {}


def add_options():
    parser = argparse.ArgumentParser(description='Geant4 simulation plotter')
    parser.add_argument('--path', '-p', metavar = 'path', help = 'path where the rootfile(s) is(are) stored')
    parser.add_argument('--outpath', '-o', metavar = 'outpath', help = 'path where the results are stored', default = "./results")
    options = vars(parser.parse_args())
    for opt in options :
        env_variables[opt] = options[opt]

    return 


def get_histograms(rfile):
    f = r.TFile.Open(rfile)
    histos = f.Get("histograms")
                          
    ret_histos = { key.GetName() : #hist_name  
         deepcopy(histos.Get(key.GetName())) for key in histos.GetListOfKeys() }
    f.Close()
    del f
    return ret_histos

def get_histograms_dict(rfiles):
    if isinstance(rfiles, str):
        env_variables["doFor"] = False
        return get_histograms( rfiles )
    env_variables["doFor"] = True
    h_dict = { re.match("^(.*)/(.*).root$", rfile)[2] : get_histograms(rfile) for rfile in rfiles }
        
    return h_dict

def get_dims(opt):
    if opt == "canvas":
        topx, topy, ww, wh = 10, 10, 1000, 800
        return ( topx, topy, ww, wh ) # last 2 for printing with 2 pads
    if opt == "legend":
        fLegX1, fLegY1, fLegX2, fLegY2 = 0.75, 0.55, 0.89, 0.89
        legendTextSize = 0.035
        return( fLegX1, fLegY1, fLegX2, fLegY2, legendTextSize )

def create_canvas(name):
    # Size of the Canvas
    # ------------------------    
    
    topx, topy, ww, wh = get_dims("canvas")
    c = r.TCanvas( 'c_' + name, '', topx, topy, ww, wh )
    return c


def print_template_histograms(histograms, key = ""):
    if (env_variables["doFor"]):
        for key in histograms:
            # prepare the results folder to store the plots
            print_template_histograms( histograms = histograms[key], key = key )
        return
    
    outpath = "/".join([env_variables["outpath"], key, "templates"]) 
    os.system("mkdir -p %s"%outpath) if not os.path.exists(outpath) else 1
    for hist in histograms:
        c = create_canvas(hist)    
        histograms[hist].Draw("hist")
        print(outpath)
        c.Print(outpath + "/%s.png"%hist, 'png')
        c.Print(outpath + "/%s.pdf"%hist, 'pdf')
    return

# === Main script
if __name__ == "__main__": 
    add_options()
    
    # Get a list of all the rootfiles in the given path
    print(env_variables)
    list_rfiles = [ "/".join([env_variables["path"], rfile]) for rfile in os.listdir(env_variables["path"]) if (".root" in rfile) == True ]
    
    # Get a dictionary with the histograms contained in the rootfiles
    histograms = get_histograms_dict( list_rfiles if len(list_rfiles) != 1 else list_rfiles[0] )
    
    print_template_histograms( histograms )
    

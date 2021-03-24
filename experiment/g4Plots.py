# ================== #
#    Main imports    #
# ================== #


import ROOT as r 
import numpy as np
import argparse
import os, sys, re
from copy import deepcopy
import canvases as cv



r.gROOT.SetBatch(1)
r.gStyle.SetOptStat(0)
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

def print_template_histograms(histograms, key = ""):
    if (env_variables["doFor"]):
        for key in histograms:
            # prepare the results folder to store the plots
            print_template_histograms( histograms = histograms[key], key = key )
        return
    
    outpath = "/".join([env_variables["outpath"], key, "templates"]) 
    os.system("mkdir -p %s"%outpath) if not os.path.exists(outpath) else 1
    for hist in histograms:
        c = cv.create_canvas(hist) 
        
        l = cv.create_legend()
        h = histograms[hist]
        h.SetMaximum(h.GetMaximum()*1.1)
        h.SetMinimum(0)
        h.Draw("hist")
        h.SetTitle("")
        l.AddEntry(h, h.GetName(), "l")
        l.Draw("same")
        
        H = r.TLatex()
        H.SetTextSize(0.07)
        H.DrawLatexNDC(0.1, 0.92,"#font[22]{FPFE} | #font[12]{Academic}")

        c.Print(outpath + "/%s.png"%hist, 'png')
        c.Print(outpath + "/%s.pdf"%hist, 'pdf')
    return
# === Main script
if __name__ == "__main__": 
    add_options()
    
    # Get a list of all the rootfiles in the given path
    list_rfiles = [ "/".join([env_variables["path"], rfile]) for rfile in os.listdir(env_variables["path"]) if (".root" in rfile) == True ]
    
    # Get a dictionary with the histograms contained in the rootfiles
    histograms = get_histograms_dict( list_rfiles if len(list_rfiles) != 1 else list_rfiles[0] )
    
    print_template_histograms( histograms )
    
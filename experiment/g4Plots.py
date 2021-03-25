# ================== #
#    Main imports    #
# ================== #


import ROOT as r 
import numpy as np
import argparse
import os, sys, re
from copy import deepcopy
import canvases as cv
import json

r.gROOT.SetBatch(1)
r.gStyle.SetOptStat(0)
env_variables = { "matching" : "(.*):(.*);(.*),(.*)" }

def add_options():
    parser = argparse.ArgumentParser(description='Geant4 simulation plotter')
    parser.add_argument('--path', '-p', metavar = 'path', help = 'path where the rootfile(s) is(are) stored')
    parser.add_argument('--outpath', '-o', metavar = 'outpath', help = 'path where the results are stored', default = "./results")
    parser.add_argument('--json', '-j', metavar = 'json', help = "Json name for storing experiments", default = 'run')
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

def set_histograms_dict(rfiles):
    ''' 
        Function to store histograms from rootfiles in a 
        custom environmental variable
    '''
    env_variables["doFor"] = False if isinstance(rfiles, str) else True
    
    doFor = env_variables["doFor"]
    
    if doFor: 
        h_dict = { re.match("^(.*)/(.*).root$", rfile)[2] : get_histograms(rfile) for rfile in rfiles }
        files = list(h_dict.keys())
    else: 
        h_dict = get_histograms(rfiles)  
        files = re.match("^(.*)/(.*).root$", rfiles).groups()[1]
    env_variables["AnalysedFiles"] = files
    env_variables["histograms"] = h_dict
    return 

def set_hists_to_plot():
    env_variables["to_plot"] = read_txt()

def read_txt():
    txt_name = "g4plots.txt"
    f = open(txt_name)
    lines = [ re.match(env_variables["matching"], line.replace(" ", "")).groups() for line in f.readlines() if ("#" not in line[0] and line!="" and line!="\n") ]
    hists_to_plot = { line[0] : line[1:] for line in lines}
    return hists_to_plot


def save_json():
    make_path("./jsons/")

    # make a copy of the environmenta variables an just save what is important about the run
    temp = env_variables.copy()
    for key in ["matching", "json", "doFor", "histograms"]:
        del temp[key]
    with open("./jsons/" + env_variables["json"] + ".json", "w") as json_file:
        json.dump(temp, json_file)
    return

def make_path(path):
    os.system("mkdir -p %s"%path) if not os.path.exists(path) else 1

def draw_histos(c, l, h, index, rfile, opts):
    opt = "hist" if index == 0 else "hist same"
    nbins, xmin, xmax = re.match("^(.*),(.*),(.*)$", opts[0].replace(" ", "").replace("[", "").replace("]","") ).groups()
    xtitle = opts[1]
    ytitle = opts[2]
    color = index if index not in [0, 5, 10] else index+1 
    if "2" in rfile: h.Scale(1.1)
    h.SetMaximum(h.GetMaximum()*1.1)
    h.SetMinimum(0)
    h.SetLineColor(color)
    h.GetXaxis().SetTitle(xtitle)
    h.GetYaxis().SetTitle(ytitle)
    h.GetYaxis().SetTitleOffset(1.3)
    h.GetYaxis().SetLabelSize(0.03)
    h.GetXaxis().SetLabelSize(0.03)
    #h.Rebin(int(nbins))
    #h.GetXaxis().SetRangeUser(float(xmin), float(xmax))
    h.SetTitle("")
    h.Draw(opt)

    l.AddEntry(h, rfile, "l")
    return c, l

def print_histograms(key = ""):
    toPlot = env_variables["to_plot"]
    histograms = env_variables["histograms"]
    doFor = env_variables["doFor"]

    outpath = "/".join([env_variables["outpath"], key, "templates"]) 
    make_path(outpath)
    
    for plot in toPlot:
        c = cv.create_canvas(plot) 
        l = cv.create_legend()
        if (doFor):
            for index, rfile in enumerate(histograms.keys()):
                c, l = draw_histos(c, l, histograms[rfile][plot], index, rfile, toPlot[plot])
                c.Modified()
        else:
            draw_histos(c, l, histograms[plot], 0, plot, toPlot[plot])
        
        l.Draw("same")
        
        H = r.TLatex()
        H.SetTextSize(0.07)
        H.DrawLatexNDC(0.1, 0.92,"#font[22]{FPFE} | #font[12]{Academic}")

        c.Print(outpath + "/%s.png"%plot, 'png')
        c.Print(outpath + "/%s.pdf"%plot, 'pdf')
    return

# === Main script
if __name__ == "__main__": 
    add_options()
    
    # Get a list of all the rootfiles in the given path
    list_rfiles = [ "/".join([env_variables["path"], rfile]) for rfile in os.listdir(env_variables["path"]) if (".root" in rfile) == True ]
    
    # Get a dictionary with the histograms contained in the rootfiles
    set_histograms_dict( list_rfiles if len(list_rfiles) != 1 else list_rfiles[0] )
    
    # Set the histograms we want to plot
    set_hists_to_plot()
    
    # Print the histograms following the txt directives.
    print_histograms()

    # Save information about this run in a json file
    save_json()
    

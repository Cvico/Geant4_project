# ================== #
#    Main imports    #
# ================== #


import ROOT as  r
import os, re, sys
from copy import deepcopy
r.gROOT.SetBatch(1)
r.gStyle.SetOptStat(0)

def make_path(path):
    os.system("mkdir -p %s"%path) if not os.path.exists(path) else 1

def get_dims(opt):
    if opt == "canvas":
        topx, topy, ww, wh = 10, 10, 1000, 800
        return ( topx, topy, ww, wh ) # last 2 for printing with 2 pads
    if opt == "legend":
        fLegX1, fLegY1, fLegX2, fLegY2 = 0.35, 0.55, 0.89, 0.89
        legendTextSize = 0.035
        return( fLegX1, fLegY1, fLegX2, fLegY2, legendTextSize )


def create_canvas(name):
    # Size of the Canvas
    # ------------------------    
    topx, topy, ww, wh = get_dims("canvas")
    c = r.TCanvas( 'c_' + name, '', topx, topy, ww, wh )
    return c


def create_legend():
    fLegX1, fLegY1, fLegX2, fLegY2, legendTextSize = get_dims("legend")
    l = r.TLegend(fLegX1, fLegY1, fLegX2, fLegY2)
    l.SetBorderSize(0)
    l.SetFillColor(10)
    l.SetTextSize(legendTextSize)
    return l


def draw_histos(args):
    if env_variables["exercise"] == 1: draw_histos_ex1(args)
    return



def draw_histos(env_variables):
   if env_variables["exercise"] == "1": draw_histos_ex1(env_variables)
   return

def draw_histos_ex1(env_variables):
   '''
	Very simple function to plot the comparison with Meroli...
   '''
   histos  = env_variables["histograms"]
   samples = env_variables["AnalysedFiles"] 
 
   outpath = env_variables["outpath"]	 
   make_path(outpath)
 
   xtitles = {"proton"  : "E(GeV)/#mum",
	      "electron": "E(MeV)/#mum" }
   
   for part in ["proton", "electron"]:	
        c = create_canvas("edep_" + part)
      	
        l1 = create_legend()      
        for index, rfile in enumerate(samples):
	     if part not in rfile: continue
             edep   = histos[rfile]["Edep"]

	     #edep.Divide(trackl)
	     if (edep.GetMaximum() == 0.0): continue
 	     thickness = float(re.match("(.*)_(.*)(um)_(.*)_(.*)", rfile).groups()[1].replace("p", "."))
	     norm = deepcopy(edep.Clone("norm_%s"%rfile))
	     for bini in range(1, edep.GetNbinsX()+1):
		norm.SetBinContent(bini, thickness)
	     edep.Divide(norm)
	     edep.Scale(1.0/(edep.GetMaximum()))

             color = index if index not in [0, 5, 10] else index+1 

	     edep.SetBinContent(edep.GetNbinsX() + 1, 0)
      	     edep.SetMinimum(0)
      	     edep.SetMarkerColor(color)
	     edep.SetMarkerStyle(20)
	     edep.SetMarkerSize(1)
      	     edep.SetTitle("")
	     
      	     edep.GetXaxis().SetTitle(xtitles[part])
      	     edep.GetYaxis().SetTitle("Normalized Events")
      	     edep.GetYaxis().SetTitleOffset(1.3)
      	     edep.GetYaxis().SetLabelSize(0.03)
      	     edep.GetXaxis().SetLabelSize(0.03)

	     edep.Draw("hist same p")	
	#    inputs/ex1/silicon_107p29um_100MeV_electrons.root 
      	     entryName = "t = %3.2f #mum"%thickness      
      	     l1.AddEntry(edep, entryName, "p")
     	l1.Draw("same") 
        H = r.TLatex()
        H.SetTextSize(0.07)                                                    	 
        H.DrawLatexNDC(0.1, 0.92,"#font[22]{FPFE} | #font[12]{Academic}")
        c.Print(outpath + "/%s.png"%( part ), 'png') 
        c.Print(outpath + "/%s.pdf"%( part ), 'pdf')

   return

# ================== #
#    Main imports    #
# ================== #


import ROOT as  r
import os, re, sys
from copy import deepcopy
import numpy as np
r.gROOT.SetBatch(1)
r.gStyle.SetOptStat(0)

def make_path(path):
    os.system("mkdir -p %s"%path) if not os.path.exists(path) else 1

def get_dims(opt):
    if opt == "canvas":
        topx, topy, ww, wh = 10, 10, 1000, 800
        return ( topx, topy, ww, wh ) # last 2 for printing with 2 pads
    if opt == "legend":
        fLegX1, fLegY1, fLegX2, fLegY2 = 0.55, 0.55, 0.89, 0.89
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


def draw_histos(env_variables):
    if env_variables["exercise"] == "1": draw_meroli_comp(env_variables)
    return

def draw_meroli_comp(env_variables):
   '''
	Very simple function to plot the comparison with Meroli and some other plots
   '''
   outpath = env_variables["outpath"]
   c = create_canvas("ex1")
   l = create_legend()

   meroli = env_variables["ret_histograms"]["Meroli"]
   sim = env_variables["ret_histograms"]["YourApplication"]
   
  # meroli.Draw("hist p")
   meroli_gr = r.TGraph(meroli)
   sim.Draw("hist")
   meroli_gr.Draw("l same") 
   sim.SetLineColor(r.kRed)
   print(sim.Integral())

   sim.Scale(meroli_gr.Integral()/sim.Integral(), "width")
   
   sim.SetMarkerColor(r.kBlack)	
#   print([sim.GetBinContent(bini) for bini in range(1, 1+sim.GetNbinsX())]) 

   
   meroli_gr.SetLineColor(r.kBlack)
#   meroli_gr.SetLineStyle(20)

   sim.SetTitle("")
   sim.SetMinimum(0)
   sim.SetMaximum(meroli.GetMaximum()*1.2)
   sim.GetXaxis().SetTitle("E(MeV)")
   sim.GetYaxis().SetTitle("Events")
   sim.GetYaxis().SetTitleOffset(1.3)
   sim.GetYaxis().SetLabelSize(0.03)
   sim.GetXaxis().SetLabelSize(0.03)
 
   l.AddEntry(meroli, "Data", "l")
   l.AddEntry(sim, "FPFE simulation", "l")
 
   l.Draw("same")
   draw_header()   
   make_path(outpath)
   c.Print(outpath + "/%s.png"%( "Meroli_comp"), 'png') 
   c.Print(outpath + "/%s.pdf"%( "Meroli_comp" ), 'pdf')

   return

def draw_header():
   H = r.TLatex()
   H.SetTextSize(0.07)                                                    	 
   H.DrawLatexNDC(0.1, 0.91,"#font[22]{FPFE} | #font[12]{Academic}")

   return

def draw_histos_ex2(env_variables):
   histos  = env_variables["histograms"]
   samples = env_variables["AnalysedFiles"] 
 
   outpath = env_variables["outpath"]	 
   make_path(outpath)
 
   xtitles = {"proton"  : "E(GeV)",
	      "electron": "E(MeV)" }
   
   for part in ["proton", "electron"]:	
      c = create_canvas("edep_" + part)
      
      l1 = create_legend()      
      for index, rfile in enumerate(samples):
         if part not in rfile: continue
         edep   = histos[rfile]["Edep"]

         if (edep.GetMaximum() == 0.0): continue
         thickness = float(re.match("(.*)_(.*)(um)_(.*)_(.*)", rfile).groups()[1].replace("p", "."))
         edep.Scale(1.0/(edep.GetMaximum()))

         color = index if index not in [0, 5, 10] else index+1 
         edep.Draw("hist same p")
      
         edep.SetMaximum(1.2)
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

           	
      #    inputs/ex1/silicon_107p29um_100MeV_electrons.root 
         entryName = "t = %3.2f #mum"%thickness      
         l1.AddEntry(edep, entryName, "p")
      l1.Draw("same") 
      c.Print(outpath + "/%s.png"%( part ), 'png') 
      c.Print(outpath + "/%s.pdf"%( part ), 'pdf')

   return





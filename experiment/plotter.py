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
        fLegX1, fLegY1, fLegX2, fLegY2 = 0.55, 0.69, 0.89, 0.89
        legendTextSize = 0.035
        return( fLegX1, fLegY1, fLegX2, fLegY2, legendTextSize )


def create_canvas(name, nPads = 1):
    # Size of the Canvas
    # ------------------------    
    topx, topy, ww, wh = get_dims("canvas")
    
    c = r.TCanvas( 'c_' + name, '', topx, topy, ww, wh )
    
    if nPads == 2:
       c.Divide(1, 2)
       p1 = c.GetPad(1)
            
       p1.SetPad(0, 0.35, 1, 0.95)
       p1.SetTopMargin(0.1)
       p1.SetBottomMargin(0.02)
       
       p2 = c.GetPad(2)
       p2.SetPad(0, 0.1, 1, 0.35)
       p2.SetTopMargin(0.1)
       p2.SetBottomMargin(0.2)
       
        
#       p1.SetGrid()
       p2.SetGrid()
    
    return c


def create_legend(args = None):
    if args == None:
      fLegX1, fLegY1, fLegX2, fLegY2, legendTextSize = get_dims("legend")
    else:
      fLegX1, fLegY1, fLegX2, fLegY2, legendTextSize = args

    l = r.TLegend(fLegX1, fLegY1, fLegX2, fLegY2)
    l.SetBorderSize(0)
    l.SetFillColorAlpha(0, 0)
    l.SetTextSize(legendTextSize)
    return l


def draw_histos(env_variables):
    if env_variables["exercise"] == "1": 
        draw_meroli_comp(env_variables)
        draw_templates(env_variables)
    if env_variables["exercise"] == "2": draw_histos_ex2(env_variables)
    if env_variables["exercise"] == "3": draw_histos_ex3(env_variables)
    if env_variables["exercise"] == "4": draw_histos_ex4(env_variables)

    return

def draw_meroli_comp(env_variables):
   '''
	Very simple function to plot the comparison with Meroli and some other plots
   '''
   outpath = env_variables["outpath"]
   c = create_canvas("ex1", nPads = 2)
   p1 = c.GetPad(1)
   p2 = c.GetPad(2)

   l = create_legend()
 
   meroli_gr = env_variables["histograms"]["Meroli"]
   sim = env_variables["histograms"]["silicon_5p6um_100MeV_electron"]["Edep"] 
   
   fitFCN_conv, fits_conv = env_variables["fitFuncs"]["convolved"]
   fitFCN_conv.SetParameters(fits_conv[0], fits_conv[1], fits_conv[2], fits_conv[3], fits_conv[4])

   fitFCN_conv.SetLineColor(r.kOrange+8)
   fitFCN_conv.SetLineStyle(9)
   fitFCN_landau, fits_landau = env_variables["fitFuncs"]["Landau"]
   fitFCN_landau.SetParameters(fits_landau[0], fits_landau[1], fits_landau[2])

   fitFCN_landau.SetLineColor(r.kTeal+5)
   fitFCN_landau.SetLineStyle(1)

   p1.cd()

   meroli_gr.Draw("la") 
   sim.Draw("hist same")
   fitFCN_conv.Draw("l same")
   fitFCN_landau.Draw("l same")

   sim.SetLineColor(r.kAzure+2)
   sim.SetLineWidth(3) 
   sim.Scale(meroli_gr.Integral()/sim.Integral(), "width")
   sim.SetMarkerColor(r.kBlack)	

    
   meroli_gr.SetLineColor(r.kBlack)

   meroli_gr.SetTitle("")
   meroli_gr.SetMinimum(0)
   meroli_gr.GetXaxis().SetRangeUser(0, meroli_gr.GetXaxis().GetXmax())
   meroli_gr.SetMaximum(max(meroli_gr.GetY())*1.2)
   meroli_gr.GetYaxis().SetTitle("Events")
   meroli_gr.GetYaxis().SetTitleOffset(1.3)
   meroli_gr.GetYaxis().SetLabelSize(0.03)
   meroli_gr.GetXaxis().SetLabelSize(0)
 

   l.AddEntry(meroli_gr, "Data", "l")
   l.AddEntry(sim, "FPFE simulation", "l")
   l.AddEntry(fitFCN_conv, "Convolved fit", "l")
   l.AddEntry(fitFCN_landau, "Landau fit", "l")
   l.Draw("same")

   draw_header()   
   
   p2.cd()
   ratio = deepcopy(sim.Clone("ratioHist"))
   for bini in range(1, ratio.GetNbinsX()+1):
	bincontent = (meroli_gr.GetY()[bini-1]-sim.GetBinContent(bini))/meroli_gr.GetY()[bini-1]
	ratio.SetBinContent(bini, bincontent)
	ratio.SetBinError(bini, sim.GetBinError(bini))

   ratio.GetXaxis().SetTitle("E(keV)")
   ratio.GetYaxis().SetTitle("#frac{Data - simulation}{Data}")
   ratio.GetYaxis().SetRangeUser(-1.2, 1.2)
   ratio.SetMarkerStyle(20)
   ratio.SetTitle("")
   ratio.GetYaxis().SetLabelSize(0.09) 
   ratio.GetXaxis().SetLabelSize(0.09) 
   ratio.GetYaxis().SetTitleSize(0.08)
   ratio.GetXaxis().SetTitleSize(0.08)
   ratio.GetYaxis().SetTitleOffset(0.55)

   ratio.Draw("hist p")
   ratio.SetMarkerSize(1)

   make_path(outpath)
   p1.cd()
   c.Print(outpath + "/%s.png"%( "Meroli_comp"), 'png') 
   c.Print(outpath + "/%s.pdf"%( "Meroli_comp" ), 'pdf')

   return

def draw_header():
   H = r.TLatex()
   H.SetTextSize(0.05)                                                    	 
   H.DrawLatexNDC(0.1, 0.91,"#font[22]{FPFE} | #font[12]{Academic}")

   return

def draw_templates(env_variables):
   for var in ["Edep", "trackL"]:
      histos  = [ deepcopy(env_variables["histograms"][key][var].Clone(key)) for key in env_variables["histograms"].keys() if key != "Meroli"]
   
      outpath = env_variables["outpath"]
      make_path(outpath)
   
      c = create_canvas("ex1_templates_%s"%var)
      
      for h in histos:
         h.Draw("hist") 

         title = "Deposited energy" if var == "Edep" else "Track length"
         h.SetLineWidth(3) 
         h.GetXaxis().SetRangeUser(0, 60)
         h.SetMinimum(0)
         h.SetLineColor(r.kBlack)
         h.SetTitle(title)
         h.GetXaxis().SetTitle("E (keV)")
         h.GetYaxis().SetTitle("Events")
         h.GetYaxis().SetTitleOffset(1.3)
         h.GetYaxis().SetLabelSize(0.03)
         h.GetXaxis().SetLabelSize(0.03)
         
#      draw_header()
   
      c.Print(outpath + "/%s.png"%( "template_%s"%var), 'png') 
      c.Print(outpath + "/%s.pdf"%( "electron_%s"%var ), 'pdf')
   return


def draw_histos_ex2(env_variables):
   histos  = [ deepcopy(env_variables["histograms"][key]["Edep"].Clone(key)) for key in env_variables["histograms"].keys() ]

   outpath = env_variables["outpath"]
   make_path(outpath)

   c = create_canvas("ex2")
   l = create_legend()

   
   for index, h in enumerate(histos):
      filelist = re.match("(.*)_(.*)(um)_(.*)_(.*)", h.GetName()).groups()
      thickness =  filelist[1].replace("p", ".")


      h.Scale(1.0/(h.Integral()))
      
      color = index+1 if index not in [0, 5, 10] else index+1 
      h.Draw("hist same")
            
      h.SetMaximum(0.5)  
      h.SetLineWidth(3) 
      h.GetXaxis().SetRangeUser(0, 60)
      h.SetMinimum(0)
      h.SetLineColor(color)
      h.SetTitle("")
      h.GetXaxis().SetTitle("E (keV)")
      h.GetYaxis().SetTitle("Normalized Events")
      h.GetYaxis().SetTitleOffset(1.3)
      h.GetYaxis().SetLabelSize(0.03)
      h.GetXaxis().SetLabelSize(0.03)

      entryName = "E = %s #mum"%thickness
      
      l.AddEntry(h, entryName, "l")

   draw_header()
   l.Draw("same") 

   c.Print(outpath + "/%s.png"%( "electron_Thicknesses"), 'png') 
   c.Print(outpath + "/%s.pdf"%( "electron_Thicknesses" ), 'pdf')
   return

def draw_histos_ex3(env_variables):
   histos = env_variables["histograms"]
   samples = histos.keys()

   outpath = env_variables["outpath"]
   make_path(outpath)
   linestyle = {"100MeV": 1, "10GeV": 8, "1GeV": 9}
   colors = {"electrons": r.kAzure + 1, "photons": r.kViolet -7, "pions":r.kOrange - 2}
   forLegend1 = {"100MeV": r.TH1D("100MeV", "", 1, 0, 1), "10GeV": r.TH1D("10GeV", "", 1, 0, 1), "1GeV": r.TH1D("1GeV", "", 1, 0, 1)}
   forLegend2 = {"electrons": r.TH1D("electrons", "", 1, 0, 1), "photons": r.TH1D("photons", "", 1, 0, 1), "pions": r.TH1D("pions", "", 1, 0, 1)}
   # Modify legend entries
   for entry in ["100MeV", "10GeV", "1GeV"]:
      forLegend1[entry].SetLineStyle(linestyle[entry])
      forLegend1[entry].SetLineWidth(3)
      forLegend1[entry].SetLineColor(1)
   for entry in ["electrons", "photons", "pions"]:
      forLegend2[entry].SetLineWidth(3)
      forLegend2[entry].SetLineColor(colors[entry])

   for var in ["Eecal", "Ehcal"]:
      c = create_canvas("ex3_%s"%var)
      l = create_legend( (0.45, 0.89, 0.91, 0.97, 0.035)  )
      l.SetNColumns(3)
      l2 = create_legend( (0.55, 0.69, 0.89, 0.89, 0.05) )

      for index, h in enumerate(histos):
         filelist = re.match("(.*)_(.*)", h).groups()
         part = filelist[0]
         
         energyval = filelist[1][:-3]
         energyunit = filelist[1].split(energyval)[1]
         
         #print(h, part, energyval, energyunit)
         h = histos[h][var]
         #h.Scale(1.0/(h.Integral()))
      
         if part == "pions" and filelist[1] == "10GeV": 
            c1 = create_canvas("ex3_%s_pions10GeV"%var)

            h.Draw("hist")
            h.SetLineWidth(3)
            h.SetLineStyle(linestyle[filelist[1]]) 
            #h.SetMinimum(0)
            h.SetLineColor(colors[part])
            h.SetTitle("#pi^{-} at 10 GeV")
            h.GetXaxis().SetTitle("E (keV)")
            h.GetYaxis().SetTitle("Events")
            h.GetYaxis().SetTitleOffset(1.3)
            h.GetYaxis().SetLabelSize(0.03)
            h.GetXaxis().SetLabelSize(0.03)
            
            draw_header()
            h.SetLineColor(colors[part])
            c1.Print(outpath + "/pions10GeV_%s.png"%var, 'png') 
            c1.Print(outpath + "/pions10GeV%s.pdf"%var, 'pdf')      
            del c1
            continue

         color = index+1 if index not in [0, 5, 10] else index+1 
         
         h.Draw("hist same")
         if filelist[1] == "10GeV": h.Scale(10)
         #h.SetMaximum(0.2)  
         h.SetLineWidth(3)
         h.SetLineStyle(linestyle[filelist[1]]) 
         #h.SetMinimum(0)
         h.SetLineColor(colors[part])
         h.SetTitle("")
         h.GetXaxis().SetTitle("E (keV)")
         h.GetYaxis().SetTitle("Events")
         h.GetYaxis().SetTitleOffset(1.3)
         h.GetYaxis().SetLabelSize(0.03)
         h.GetXaxis().SetLabelSize(0.03)

         h.SetLineColor(colors[part])
      
      l.AddEntry(forLegend1["100MeV"], "100 MeV", "l")
      l.AddEntry(forLegend1["1GeV"], "1 GeV", "l")
      l.AddEntry(forLegend1["10GeV"], "(10 GeV) x 10 ", "l")
      l.Draw("same")   
      l2.AddEntry(forLegend2["photons"], "e^{-}", "l")
      l2.AddEntry(forLegend2["electrons"], "#gamma", "l")
      l2.AddEntry(forLegend2["pions"], "#pi^{-}", "l")
      l2.Draw("same")   
      draw_header()
      #l2.Draw("same")
      c.Print(outpath + "/%s.png"%( "%s"%(var) ), 'png') 
      c.Print(outpath + "/%s.pdf"%( "%s"%(var) ), 'pdf')
   return







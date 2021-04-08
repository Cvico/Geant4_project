# ================== #
#    Main imports    #
# ================== #


import ROOT as  r
import os, re, sys
r.gROOT.SetBatch(1)
r.gStyle.SetOptStat(0)

def make_path(path):
    os.system("mkdir -p %s"%path) if not os.path.exists(path) else 1

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

def create_legend():
    fLegX1, fLegY1, fLegX2, fLegY2, legendTextSize = get_dims("legend")
    l = r.TLegend(fLegX1, fLegY1, fLegX2, fLegY2)
    l.SetBorderSize(0)
    l.SetFillColor(10)
    l.SetTextSize(legendTextSize)
    return l


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

def print_histograms(env_variables, key = ""):
    toPlot = env_variables["to_plot"]
    histograms = env_variables["histograms"]
    doFor = env_variables["doFor"]

    outpath = "/".join([env_variables["outpath"], key, "templates"]) 
    make_path(outpath)
    
    for plot in toPlot:
        c = create_canvas(plot) 
        l = create_legend()
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

   

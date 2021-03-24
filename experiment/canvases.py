import ROOT as r 

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





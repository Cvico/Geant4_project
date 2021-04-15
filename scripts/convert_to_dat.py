import ROOT as r
import sys
rfile = sys.argv[1]

# Open the rootfile
f = r.TFile.Open(rfile)

tree = f.Get("histograms")
l = tree.GetListOfKeys()
for key in l:
   h = tree.Get(key.GetName())
   # Open outputfile
   outfile = open(key.GetName() + ".dat", "w")
   outfile.write("%s \t %s \t %s \n"%("Bin", key.GetName(), "Bin height"))
   for bini in range(1, 1 + h.GetNbinsX()):
	outfile.write("%d \t %3.3f \t %3.3f \n"%(bini, h.GetBinCenter(bini), h.GetBinContent(bini)))
   outfile.close()

f.Close()

import plotter as g4plt

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
    print_histograms(env_variables)

    # Save information about this run in a json file
    save_json()
 

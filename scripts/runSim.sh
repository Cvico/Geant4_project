#!/bin/bash
# ================================================================================================= #
#               In this script I have compiled different ways of executing the simulation           #
#  ------------------------------------------------------------------------------------------------ #
#                                                                                                   #        
#   The script takes three arguments: (1) for simulating, (2) for plotting and (3) for both         #
#                                                                                                   #
# ================================================================================================= #


MODE="$1"

# Some formatting colors for output
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

plot() {
    cd "./experiment"
    
    INPATH="../build"
    OUTPUTRESULTPATH="./results"
    COMMAND="g4Plots.py --path $INPATH --outpath $OUTPUTRESULTPATH"

    echo -e "${GREEN}[INFO]${NC}: Running plotting script:"
    python $COMMAND
    cd ..
}

compile () {
    buildFolder="./build"

    if [[ ! -d $buildFolder ]]
    then
        echo -e "${GREEN}[INFO]${NC}: The folder ${buildFolder} does not exist"
        echo "                     ... Creating folder to build code"
        mkdir $buildFolder
    fi

    cd $buildFolder

    # Compile libraries
    cmake -DGeant4_DIR=$G4LIB -DGEANT4_USE_OPENGL_X11=ON ../
    make


    # Compile the macro to check if everything works fine+

    echo -e "${GREEN}[COMPILING MSG]${NC} ========= COMPILING MACRO ==========="
    ./main run1.mac
    echo -e "${GREEN}[COMPILING MSG]${NC} ========= END OF COMPILATION ========"
    # Return to the previous folder
    cd ..   
}
# Default MODE=1
if [[ $MODE == "" ]]
then
    echo -e "${BLUE}[WARNING]${NC}: No mode has been specified... Running MODE=1 as default. See README for more information about compiling modes"
    compile
fi

if [[ $MODE == 1 ]] # COMPILE AND RUN THE .MAC FILE
then
    compile
fi

if [[ $MODE == 2 ]] # Plot results
then 
    plot  
fi

if [[ $MODE == 3 ]] # Compile and plot results
then 
    compile
    plot  
fi


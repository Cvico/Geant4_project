#!/bin/bash
# ================================================================================================= #
#               In this script I have compiled different ways of executing the simulation           #
#  ------------------------------------------------------------------------------------------------ #
#                                                                                                   #        
#   The script takes three arguments: (1) for simulating, (2) for plotting and (3) for both         #
#                                                                                                   #
# ================================================================================================= #


MODE="$1"
MACRO="$2"

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
    cmake3 -DGeant4_DIR=$G4COMP ../
    make


    # Compile the macro to check if everything works fine+

    echo -e "${GREEN}[COMPILING MSG]${NC} ========= COMPILING MACRO ==========="
    ./main $MACRO
    echo -e "${GREEN}[COMPILING MSG]${NC} ========= END OF COMPILATION ========"
    # Return to the previous folder
    cd ..  

    # Now copy the output rootfile to the ./experiment/inputs path so we can store 
    # these rootfiles for later use without having to compile again
    cp "./build *.root ./experiment/inputs"
	 
}

# Default MODE=1
if [[ $MODE == "" ]]
then
    echo -e "${BLUE}[WARNING]${NC}: No mode has been specified... See README for more information about compiling modes"
fi


if [[ $MODE == 1 ]] # COMPILE AND RUN THE .MAC FILE
then
   if [[ $MACRO == ""]] 
   then
      echo -e "${RED}[ERROR]${NC}: Please, select a run macro to run from the ./macros folder"
   fi

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


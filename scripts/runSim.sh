#!/bin/bash
# ================================================================================================= #
#                                                                                                   #        
#   The script takes an exercise as an argument. Each exercise corresponds with one section 	    #
#   of the final report.								            #
#                                                                                                   #
# ================================================================================================= #

MODE=$1
EXERCISE=$2

# Some formatting colors for output
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'

runExercise() {
    cd "./build"

    MACROSTORUN=("run1.mac")


    echo -e "${GREEN}[COMPILING MSG]${NC} ========= BEGINING SIMULATION ==========="
     
    for f in ${MACROSTORUN[@]}
    do
        ./main $f
    done

    echo -e "${GREEN}[COMPILING MSG]${NC} ========= FINISHING SIMULATION ========"
    # Return to the previous folder
    cd ..  

    # Now copy the output rootfile to the ./experiment/inputs path so we can store 
    # these rootfiles for later use without having to compile again
    OUTPUTFOLDER="./experiment/inputs/ex"$EXERCISE
    mkdir $OUTPUTFOLDER
    cp ./build/*.root $OUTPUTFOLDER
	
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
}

if [[ $MODE == 1 ]]; then
	compile
fi
if [[ $MODE == 2 ]]; then
	runExercise
fi

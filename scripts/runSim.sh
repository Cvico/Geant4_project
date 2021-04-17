#!/bin/bash
# ================================================================================================= #
#                                                                                                   #        
#   The script takes an exercise as an argument. Each exercise corresponds with one section 	    #
#   of the final report.								            #
#                                                                                                   #
# ================================================================================================= #

MODE=$1
EXERCISE=$2

runExercise() {
    cd "./build"

    MACROSPATH="../macros/ex$EXERCISE"
    cd $MACROSPATH
    MACROSTORUN=$(ls *.mac)
    cd -

    echo $MACROSTORUN
    OUTPUTFOLDER="../experiment/inputs/ex"$EXERCISE
    echo -e "[COMPILING MSG] ========= BEGINING SIMULATION ==========="
        mkdir -p $OUTPUTFOLDER    
    for f in ${MACROSTORUN[@]}
    do
	OUTPUTNAME=$(echo $f | awk -F'.mac' '{print $1}')
        ./main $MACROSPATH/$f
	cp ./main.root $OUTPUTFOLDER/$OUTPUTNAME.root

    done
    echo -e "[COMPILING MSG] ========= FINISHING SIMULATION ========"
    # Return to the previous folder
    cd ..  
}

compile () {
    buildFolder="./build"

    if [[ ! -d $buildFolder ]]
    then
        echo -e "[INFO]: The folder ${buildFolder} does not exist"
        echo "                     ... Creating folder to build code"
        mkdir $buildFolder
    fi

    cd $buildFolder

    # Compile libraries
    cmake -DGeant4_DIR=$G4COMP ../
    make

    cd ..
}

if [[ $MODE == 1 ]]; then
	compile
fi
if [[ $MODE == 2 ]]; then
	runExercise
fi

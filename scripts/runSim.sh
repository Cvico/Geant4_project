#!/bin/bash
# ================================================================================================= #
#               In this script I have compiled different ways of executing the simulation           #
#  ------------------------------------------------------------------------------------------------ #
#                                                                                                   #        
#   The script takes three arguments: (1) for simulating, (2) for plotting and (3) for both         #
#                                                                                                   #
# ================================================================================================= #


MODE="$1"
OUTPUTFOLDER="$2"

plot() {
    cd "./experiment"
    
    
    if [[ $OUTPUTFOLDER == "" ]]
    then
        OUTPUTRESULTPATH="./results"
    else 
        OUTPUTRESULTPATH=$OUTPUTFOLDER
    fi
    COMMAND="plot_histograms.py --path ../build --outpath $OUTPUTRESULTPATH"
    echo "Running plotting script:"

    python $COMMAND
    cd ..
}

compile () {

    # Make sure you run the macro in the 
    # Check if the build folder has already been created
    buildFolder="./build"
    if [[ ! -d $buildFolder ]]
    then
        echo "The folder ${buildFolder} does not exist"
        echo "... Creating folder to build code"
        mkdir $buildFolder
    fi

    # Then cd to that folder and compile with Cmake
    cd $buildFolder



    # Compile libraries
    cmake -DGeant4_DIR=$G4LIB ../
    make


    # Compile the macro to check if everything works fine+


    echo "========= COMPILING MACRO ==========="
    ./main run.mac
    echo "========= END OF COMPILATION ========"
    # Return to the previous folder
    cd ..   
}
# Default MODE=1
if [[ $MODE == "" ]]
then
    echo "No mode has been specified... Running MODE=1 as default. See README for more information about compiling modes"
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

if [[ $MODE == 3 ]] # Compile Plot results
then 
    compile
    plot  
fi
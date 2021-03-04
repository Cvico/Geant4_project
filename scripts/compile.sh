#!/bin/bash
# An script for quickly compiling the code

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

# Return to the previous folder
cd ..   

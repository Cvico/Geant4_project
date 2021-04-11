#!/bin/bash

# Just an script for generating .mac for different thickness with the same format than
# the one just by Merioli's

# example: silicon_5p6um_100MeV_electrons.mac


# Parameters for the script

THICKNESS=$1
ENERGY=$2
PARTICLE=$3
OUTPATH=$4

TEMPLATE="template.mac"


# Extract the energy value and the unit from the input
ENERGYVAL=$(echo $ENERGY | awk -F'_' '{print $1}')
UNIT=$(echo $ENERGY | awk -F'_' '{print $2}')
# Convert the thickness to a string of the type: 5.6-->5p6 so it can be used in the name of the output mac file
THICKNESSTRING=$(echo $THICKNESS | sed -e 's/\./p/')


FILENAME="silicon_"$THICKNESSTRING"um_"$ENERGYVAL$UNIT"_"$PARTICLE.mac

echo $FILENAME

# Copy the templates
echo "copying templates..."
cp $TEMPLATE $FILENAME


# Now edit the file
# Change thickness
cat $FILENAME | sed -e "s/5.6/$THICKNESS/" > temp.mac | mv temp.mac $FILENAME

# Change Energy of the gun of particles
cat $FILENAME | sed -e "s/100 MeV/$ENERGYVAL $UNIT/" > temp.mac | mv temp.mac $FILENAME

# Change the Particle that is being studied
cat $FILENAME | sed -e "s/e-/$PARTICLE-/" > temp.mac | mv temp.mac $FILENAME


echo "Finished."

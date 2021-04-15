#!/bin/bash

# Just an script for generating .mac for different thickness with the same format than
# the one just by Merioli's

# example: silicon_5p6um_100MeV_electrons.mac


# Parameters for the script

MATERIAL=$1
THICKNESS=$2
ENERGY=$3
PARTICLE=$4
OUTPATH=$5

TEMPLATE="template.mac"

# Some naming conventions

if [[ $MATERIAL == "silicon" ]]; then MATERIALNAME="G4_Si"; fi
if [[ $MATERIAL == "argon" ]]; then MATERIALNAME="G4_Ar"; fi
if [[ $MATERIAL == "aluminum" ]]; then MATERIALNAME="G4_Al"; fi
if [[ $MATERIAL == "iron" ]]; then MATERIALNAME="G4_Fe"; fi
if [[ $MATERIAL == "lAr" ]]; then MATERIALNAME="G4_lAr"; fi
if [[ $MATERIAL == "lead" ]]; then MATERIALNAME="G4_Pb"; fi

if [[ $PARTICLE == "e" ]];then PARTICLENAME="electron"; fi
if [[ $PARTICLE == "proton" ]];then PARTICLENAME="proton"; fi
if [[ $PARTICLE == "mu" ]];then PARTICLENAME="muon"; fi

# Extract the energy value and the unit from the input
ENERGYVAL=$(echo $ENERGY | awk -F'_' '{print $1}')
UNIT=$(echo $ENERGY | awk -F'_' '{print $2}')


# Convert the thickness to a string of the type: 5.6_unit -->5p6unit so it can be used in the name of the output mac file
THICKNESSVAL=$(echo $THICKNESS | awk -F'_' '{print $1}')
THICKNESSUNIT=$(echo $THICKNESS | awk -F'_' '{print $2}')
THICKNESSTRING=$(echo $THICKNESSVAL | sed -e 's/\./p/')


FILENAME=$MATERIAL"_"$THICKNESSTRING$THICKNESSUNIT"_"$ENERGYVAL$UNIT"_"$PARTICLENAME.mac

echo $FILENAME

# Copy the templates
echo "copying templates..."
cp $TEMPLATE $FILENAME


# Now edit the file
# Change material
cat $FILENAME | sed -e "s/Silicon/$MATERIAL/" > temp.mac | mv temp.mac $FILENAME
cat $FILENAME | sed -e "s/G4_Si/$MATERIALNAME/" > temp.mac | mv temp.mac $FILENAME

# Change thickness
cat $FILENAME | sed -e "s/5.6 um/$THICKNESSVAL $THICKNESSUNIT/" > temp.mac | mv temp.mac $FILENAME

# Change Energy of the gun of particles
cat $FILENAME | sed -e "s/100 MeV/$ENERGYVAL $UNIT/" > temp.mac | mv temp.mac $FILENAME



## Change the Particle that is being studied
cat $FILENAME | sed -e "s/e-/$PARTICLE-/" > temp.mac | mv temp.mac $FILENAME


echo "Finished."

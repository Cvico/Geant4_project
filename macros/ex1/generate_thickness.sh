#!/bin/bash

# Just an script for generating .mac for different thickness with the same format than
# the one just by Merioli's

# example: silicon_5p6um_100MeV_electrons.mac

TEMPLATE_ELECTRONS="silicon_5p6um_100MeV_electrons.mac"
TEMPLATE_PROTONS="silicon_5p6um_12GeV_protons.mac"

THICKNESS=$1
THICKNESSTRING=$(echo $THICKNESS | sed -e 's/\./p/')

FILENAME_ELE="silicon_"$THICKNESSTRING"_100MeV_electrons.mac"
FILENAME_PRO="silicon_"$THICKNESSTRING"_12GeV_protons.mac"

# Copy the templates
echo "copying templates..."
cp $TEMPLATE_ELECTRONS $FILENAME_ELE
cp $TEMPLATE_PROTONS $FILENAME_PRO


# Now edit those files
echo "editing files..."
cat $FILENAME_ELE | sed -e "s/5.6/$THICKNESS/" > temp.mac | mv temp.mac $FILENAME_ELE
cat $FILENAME_PRO | sed -e "s/5.6/$THICKNESS/" > temp.mac | mv temp.mac $FILENAME_PRO

echo "Finished."

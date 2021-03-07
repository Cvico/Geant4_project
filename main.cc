#include <iostream>
#include "G4Types.hh"
#include "globals.hh"
#include "include/Materials.hh"

// HERE 
#include "G4NistManager.hh"
using namespace CLHEP;

int main() {
    Materials * obj = new Materials();
    obj->addMaterial("G4_Al");
    obj->addMaterial("G4_Si");
    G4Material* matU = new G4Material("Uranium", 92., 238.03*g/mole, 18.950*g/cm3);
    obj->addMaterial(matU);
    obj->getListOfMaterials();
    return 0;
}

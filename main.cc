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
    obj->getListOfMaterials();
    return 0;
}

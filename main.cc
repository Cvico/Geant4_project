#include <iostream>
#include "G4Types.hh"
#include "globals.hh"
#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "Materials.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

using namespace CLHEP;


void importMaterials(Materials* obj){
    // Import all the materials we want to have available for detector
    // construction. Define here the materials

    //  -- See: http://www.apc.univ-paris7.fr/~franco/g4doxy/html/classG4Material.html
    //  for more information on different constructors.
    obj->addMaterial("G4_Al");
    obj->addMaterial("G4_Si");
    obj->addMaterial(new G4Material("Uranium", 92., 238.03*g/mole, 18.950*g/cm3));
    obj->addMaterial(new G4Material("air", 1.290*mg/cm3, 2));
    obj->addMaterial(new G4Material("aerogel", 0.2*g/cm3, 3));
    obj->addMaterial("G4_lAr");
    obj->addMaterial("G4_CONCRETE");

    //  -- See: http://www.apc.univ-paris7.fr/~franco/g4doxy/html/classG4Element.html
    //  for more information on different constructors.
    obj->addElement(new G4Element("Nytrogen", "N", 7.0, 14.0067*g/mole));
    obj->addElement(new G4Element("Oxygen", "O", 8.0, 16.0*g/mole));
    obj->addElement(new G4Element("Hydrogen", "H", 1.0, 1.01*g/mole));

    //  -- See: http://www.apc.univ-paris7.fr/~franco/g4doxy/html/classG4Isotope.html
    //  for more information on different constructors.

    return;
}


int main(){
    /*
    Materials * obj = new Materials();
    importMaterials(obj);
    // Get a list of all the materials included
    // Call the destructor for freeing memory
    obj->printListOfElements();
    obj->~Materials();
    */
    DetectorConstruction * detector = new DetectorConstruction();
    detector->buildSolidWorld();
    detector->buildLogicalWorld();
    detector->buildPhysicalWorld();
    G4VPhysicalVolume* world = detector->getPhysicalWorld();
    return 0;
}

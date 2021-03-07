
#include "DetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

DetectorConstruction::DetectorConstruction() 
: G4VUserDetectorConstruction() {
  // set default target material
  G4String matName = "G4_Si";
  fTargetMaterial  = G4NistManager::Instance()->FindOrBuildMaterial(matName);
  if (fTargetMaterial == nullptr) {
    G4cerr << "  ERROR DetectorConstruction() \n" 
           << "  Material with name " << matName << " was not found! \n"
           << G4endl;
  }
  // set default target thickness
  fTargetThickness = 1.0*CLHEP::cm;  
}

DetectorConstruction::~DetectorConstruction(){}


G4VPhysicalVolume* DetectorConstruction::Construct() {

  return 0;
}

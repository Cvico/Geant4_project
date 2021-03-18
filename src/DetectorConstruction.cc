#include <iostream>
#include "G4Types.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4PhysListFactory.hh"
#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "Materials.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"



DetectorConstruction::DetectorConstruction() 
: G4VUserDetectorConstruction(),
  fTargetMaterial(nullptr),
  fTargetPhysical(nullptr) { 
  
  setTargetMaterial( G4NistManager::Instance()->FindOrBuildMaterial("G4_Si") );
  setTargetThickness( 1.0*CLHEP::cm );
  
  fDetMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction(){}

void DetectorConstruction::setTargetMaterial(G4Material* mat){
  checkValidity(mat);
  fTargetMaterial = mat;
}

void DetectorConstruction::setTargetMaterial(const G4String matname){
  fTargetMaterial = G4NistManager::Instance()->FindOrBuildMaterial(matname);
  checkValidity(fTargetMaterial);
}

void DetectorConstruction::setTargetThickness(G4double targetThickness){ fTargetThickness = targetThickness; }

void DetectorConstruction::buildSolidWorld(){
  fSolidWorld= new G4Box("solid-world", fWorldXsize, fWorldYsize, fWorldZsize);
  return;
}

void DetectorConstruction::buildLogicalWorld(){
  fLogicalWorld = new G4LogicalVolume(fSolidWorld, fTargetMaterial, "logical-world");
  return;
}

void DetectorConstruction::buildPhysicalWorld(){
// build and return the physical world  
  fWorldPhysical = new G4PVPlacement(nullptr, //(no) rotation
                                     G4ThreeVector(0., 0., 0.), //translation
                                     fLogicalWorld, // logical world
                                     "phys-world",  // name
                                     nullptr,  //Mother volume
                                     false, // don't care
                                     0); //cpy number;
  return;
}

void DetectorConstruction::buildSolidTarget(){
  fTargetSolid = new G4Box("solid-target", fTargetXsize, fTargetYsize, fTargetZsize);
  return;
}

void DetectorConstruction::buildLogicalTarget(){
  fTargetLogical = new G4LogicalVolume(fTargetSolid, fTargetMaterial, "logical-target");
  return;
}

void DetectorConstruction::buildPhysicalTarget(){
  // build and return the physical world  
  fTargetPhysical = new G4PVPlacement(nullptr, //(no) rotation
                                     G4ThreeVector(0., 0., 0.), //translation
                                     fTargetLogical,
                                     "Target",
                                     fLogicalWorld, // logical world
                                     false, // don't care
                                     0); //cpy number;
  return;
}
G4VPhysicalVolume* DetectorConstruction::Construct() {
  // II. CREATE GEOMETRY:
  // 1. Define target and world sizes
  setTargetXsize(fTargetThickness);
  setTargetYsize(1.25*fTargetThickness);
  setTargetZsize(1.25*fTargetThickness);
  setWorldXsize(1.1*fTargetXsize);
  setWorldYsize(1.1*fTargetYsize);
  setWorldZsize(1.1*fTargetZsize);
  setGunXPosition(-0.25*(fWorldXsize + fTargetThickness));  
  setGunYPosition(0.0);  
  setGunZPosition(0.0);  
  // Create worlds
  buildSolidWorld();
  buildLogicalWorld();
  buildPhysicalWorld();

  buildSolidTarget();
  buildLogicalTarget();
  buildPhysicalTarget();

  // Create targets:
  return fWorldPhysical;
}




void DetectorConstruction::checkValidity(G4Material* mat){
  if (mat == nullptr) {
      G4cerr<< "\n **** ERROR in YourDetectorConstruction::SetTargetMaterial() \n"
            << "        Material with the given name of < " << mat->GetName() << " >  \n"
            << "        was not found in the G4 NIST material DB               \n"
            << G4endl;
      exit(-1);      
    }
}

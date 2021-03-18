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
: G4VUserDetectorConstruction() { 
  DetectorConstruction(G4NistManager::Instance()->FindOrBuildMaterial("G4_Si"),
                       1.0*CLHEP::cm);
}

DetectorConstruction::DetectorConstruction(G4Material* mat) 
: G4VUserDetectorConstruction() { // Method inheritance 
  // defaultThickness = 1.0*CLHEP::cm
  DetectorConstruction(mat, 1.0*CLHEP::cm); // call the complete constructor
}

DetectorConstruction::DetectorConstruction(G4Material* mat, G4double targetThickness) 
: G4VUserDetectorConstruction() { // Method inheritance 
  checkValidity(mat);
  fTargetMaterial  = mat;
  fTargetThickness = targetThickness;  
  fDetMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction(){}


void DetectorConstruction::buildSolidWorld(){
  buildSolidWorld("solid-world", 0.5*fWorldXsize, 0.5*fWorldYsize, 0.5*fWorldZsize);
  return;
}

void DetectorConstruction::buildSolidWorld(G4String Name){
  buildSolidWorld(Name, fWorldXsize, fWorldYsize, fWorldZsize);
  return;
}

void DetectorConstruction::buildSolidWorld(G4String Name, G4double worldXsize, G4double worldYsize, G4double worldZsize){
  fBox = new G4Box(Name, worldXsize, worldYsize, worldZsize);
  return;
}

void DetectorConstruction::buildLogicalWorld(){
  // This method will be used to build the logical
  // world that is later passed to the physical one
  buildLogicalWorld("logic-world");
  return;
}

void DetectorConstruction::buildLogicalWorld(G4String Name){
  // This method will be used to build the logical
  // world that is later passed to the physical one
  fLogicalVolume = new G4LogicalVolume(fBox, fTargetMaterial, Name);
  return;
}


void DetectorConstruction::buildPhysicalWorld(){
  // This method will be used to build the logical
  // world that is later passed to the physical one
  buildPhysicalWorld("World");
  return;
}

void DetectorConstruction::buildPhysicalWorld(G4String Name){
  // This method will be used to build the logical
  // world that is later passed to the physical one
  fPhysicalVolume = new G4PVPlacement(nullptr, //(no) rotation
                                     G4ThreeVector(0., 0., 0.), //translation
                                     Name,  // name
                                     fLogicalVolume, // logical world
                                     fPhysicalVolume,  //Mother volume
                                     false, // don't care
                                     0); //cpy number
  return;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
  // This method is used to finally construct the detector
  // once all the required parameters have been defined
  buildSolidWorld();
  buildLogicalWorld();
  buildPhysicalWorld();
  return 0;
}

G4VPhysicalVolume* DetectorConstruction::Construct(G4String Name) {
  // This method is used to finally construct the detector
  // once all the required parameters have been defined
  buildSolidWorld(Name.append("_solid"));
  buildLogicalWorld(Name.append("_logic"));
  buildPhysicalWorld(Name);
  return 0;
}
G4VPhysicalVolume* DetectorConstruction::Construct(G4String Name, G4double WorldXsize, G4double WorldYsize, G4double WorldZsize) {
  // This method is used to finally construct the detector
  // once all the required parameters have been defined
  buildSolidWorld(Name.append("_solid"), WorldXsize, WorldYsize, WorldZsize);
  buildLogicalWorld(Name.append("_logic"));
  buildPhysicalWorld(Name);
  return 0;
}


void DetectorConstruction::setTargetMaterial(G4String matName){
    G4Material* mat = G4NistManager::Instance()->FindOrBuildMaterial(matName);
    checkValidity(mat);
    fTargetMaterial = mat;
}

void DetectorConstruction::checkValidity(G4Material* mat){
  if (mat == nullptr) {
      G4cerr << "  ERROR DetectorConstruction() \n" 
            << "  Material with name " << mat->GetName() << " was not found! \n"
            << G4endl;
    }
}

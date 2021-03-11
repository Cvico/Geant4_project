
#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "Materials.hh"
#include "G4Box.hh"
class G4Material;

class DetectorConstruction : public G4VUserDetectorConstruction {
public: 
   DetectorConstruction();
   DetectorConstruction(G4Material* mat);
   DetectorConstruction(G4Material* mat, G4double targetThickness);
  ~DetectorConstruction();

  // Getters
  G4Box* getSolidWorld();
  G4LogicalVolume* getLogicalWorld();
  G4VPhysicalVolume* getPhysicalWorld();
  // Setters
  void setMaterial(G4Material* mat);

  // methods to build solid world
  void buildSolidWorld();
  void buildSolidWorld(G4String Name);
  void buildSolidWorld(G4String Name, G4double worldXsize, G4double worldYsize, G4double worldZsize);
  // methods to build logical world
  void buildLogicalWorld();
  void buildLogicalWorld(G4String Name);
  // methods to build physical world
  void buildPhysicalWorld();
  void buildPhysicalWorld(G4String Name);
  // Don't really understand what this method is thought for
  virtual G4VPhysicalVolume* Construct();
  virtual G4VPhysicalVolume* Construct(G4String Name);
  virtual G4VPhysicalVolume* Construct(G4String Name, G4double worldXsize, G4double worldYsize, G4double worldZsize);


  void checkValidity(G4Material* mat);
  
  
private:
  G4Material* fTargetMaterial;   
  G4Box*      fSolidWorld;
  G4LogicalVolume* fLogicalWorld;
  G4VPhysicalVolume* fPhysicalWorld;
  G4double    fTargetThickness;
  G4double   fWorldXsize = 1*CLHEP::m;
  G4double   fWorldYsize = 1*CLHEP::m;
  G4double   fWorldZsize = 1*CLHEP::m;
};

#endif


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
  virtual G4VPhysicalVolume* getPhysicalWorld();
  // Setters
  virtual void setMaterial(G4Material* mat);

  // methods to build solid world
  virtual void buildSolidWorld();
  virtual void buildSolidWorld(G4String Name, G4double worldXsize, G4double worldYsize, G4double worldZsize);
  // methods to build logical world
  virtual void buildLogicalWorld();
  virtual void buildLogicalWorld(G4String Name);
  // methods to build physical world
  virtual void buildPhysicalWorld();
  virtual void buildPhysicalWorld(G4String Name);
  // Don't really understand what this method is thought for
  virtual G4VPhysicalVolume* Construct();
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

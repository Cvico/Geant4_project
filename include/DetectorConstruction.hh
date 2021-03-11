
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

  G4Material* GetMaterial(){ return fTargetMaterial;};
  G4double GetTargetThickness(){ return fTargetThickness;};
  G4double GetGunXPosition(){ return fGunXPosition;};
  G4double GetGunYPosition(){ return fGunYPosition;};
  G4double GetGunZPosition(){ return fGunZPosition;};

  // Setters
  void setMaterial(G4Material* mat){ fTargetMaterial = mat;};
  void setTargetThickness(G4double targetThickness){ fTargetThickness = targetThickness;};
  void SetGunXPosition(G4double GunXPosition){ fGunXPosition = GunXPosition;};
  void SetGunYPosition(G4double GunYPosition){ fGunYPosition = GunYPosition;};
  void SetGunZPosition(G4double GunZPosition){ fGunZPosition = GunZPosition;};

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

  // Method to finally build the detector
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


  G4double fGunXPosition = 1*CLHEP::m;
  G4double fGunYPosition = 1*CLHEP::m;
  G4double fGunZPosition = 1*CLHEP::m;
};

#endif

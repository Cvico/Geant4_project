
#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4Box.hh"
class G4Material;
class DetectorMessenger;

/**
 A User-defined class used for setting up the required attributes that define a detector. 
 This class inherits from G4VUserDetectorConstruction, whose documentation can be found at
 [ADD LINK TO THE DOCUMENTATION]
 */
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  DetectorConstruction();

  ~DetectorConstruction();

  // Getters

  G4Box *GetTargetBox() { return fTargetSolid; }
  G4LogicalVolume *GetTargetLogicalVolume() { return fTargetLogical; }
  G4VPhysicalVolume *GetTargetPhysicalVolume() { return fTargetPhysical; }

  G4Material *GetTargetMaterial() { return fTargetMaterial; };
  G4double GetTargetThickness() { return fTargetThickness; };
  G4double GetGunXPosition() { return fGunXPosition; };
  G4double GetGunYPosition() { return fGunYPosition; };
  G4double GetGunZPosition() { return fGunZPosition; };

  // Setters

  void setTargetMaterial(G4Material* mat);
  void setTargetMaterial(const G4String matName);
  void setTargetThickness(G4double targetThickness);
  void setGunXPosition(G4double GunXPosition) { fGunXPosition = GunXPosition; };
  void setGunYPosition(G4double GunYPosition) { fGunYPosition = GunYPosition; };
  void setGunZPosition(G4double GunZPosition) { fGunZPosition = GunZPosition; };
  void setWorldXsize(G4double worldXsize) { fWorldXsize = worldXsize; };
  void setWorldYsize(G4double worldYsize) { fWorldYsize = worldYsize; };
  void setWorldZsize(G4double worldZsize) { fWorldZsize = worldZsize; };
  void setTargetXsize(G4double targetXsize) { fTargetXsize = targetXsize; };
  void setTargetYsize(G4double targetYsize) { fTargetYsize = targetYsize; };
  void setTargetZsize(G4double targetZsize) { fTargetZsize = targetZsize; };
  // methods to build solid world
  
  // Setters

  void buildSolidWorld();
  void buildLogicalWorld();
  void buildPhysicalWorld();
  void buildSolidTarget();
  void buildLogicalTarget();
  void buildPhysicalTarget();

  virtual G4VPhysicalVolume *Construct();

  void checkValidity(G4Material *mat);

private:
  G4Material *fTargetMaterial;

  // For worlds
  G4Box *fSolidWorld = nullptr;
  G4LogicalVolume *fLogicalWorld = nullptr;
  G4VPhysicalVolume *fWorldPhysical;

  // For targets
  G4Box *fTargetSolid = nullptr;
  G4LogicalVolume *fTargetLogical = nullptr;
  G4VPhysicalVolume *fTargetPhysical;

  G4double fTargetThickness;

  G4double fWorldXsize;
  G4double fWorldYsize;
  G4double fWorldZsize;

  G4double fTargetXsize;
  G4double fTargetYsize;
  G4double fTargetZsize;

  G4double fGunXPosition;
  G4double fGunYPosition;
  G4double fGunZPosition;

  DetectorMessenger* fDetMessenger; 
};

#endif


#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class G4Material;

class DetectorConstruction : public G4VUserDetectorConstruction {
public: 
   DetectorConstruction();
  ~DetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
  
  
  
private:
  
  G4Material* fTargetMaterial;   
  
  G4double    fTargetThickness;
  
};

#endif

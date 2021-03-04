
#ifndef YOURDETECTORCONSTRUCTION_HH
#define YOURDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"

class G4Material;

class YourDetectorConstruction : public G4VUserDetectorConstruction {
public: 
   YourDetectorConstruction();
  ~YourDetectorConstruction();
  
  virtual G4VPhysicalVolume* Construct();
  
  
  
private:
  
  G4Material* fTargetMaterial;   
  
  G4double    fTargetThickness;
  
};

#endif

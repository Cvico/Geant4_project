#include <iostream>
#include "G4Types.hh"
#include "globals.hh"

// HERE 
#include "G4NistManager.hh"


int main() {
  
  // the code must go here
  // this is some example to play with
  // try here all the commands that we saw in class
  
  const G4String elName = "Al";
  G4NistManager::Instance()->PrintElement(elName);
  
  const G4String matCName = "simple";
  G4NistManager::Instance()->ListMaterials(matCName);
  
  const G4String matName = "G4_Si_askjgd asdgh";
  const G4Material* theSi = G4NistManager::Instance()->FindOrBuildMaterial(matName);
  if (theSi != nullptr) {
    G4cout << theSi << G4endl;
  } else {
    G4cout << " nothing: " << matName << G4endl;
  }
  
  return 0;
}

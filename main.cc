#include <iostream>
#include "G4Types.hh"
#include "globals.hh"

// HERE 
#include "G4NistManager.hh"

using namespace CLHEP;
int main() {
  
  // the code must go here
  // this is some example to play with
  // try here all the commands that we saw in class
  
  const G4String elName = "Al";
  G4NistManager::Instance()->PrintElement(elName);
  
  const G4String matCName = "simple";
  G4NistManager::Instance()->ListMaterials(matCName);
  
  const G4String matName = "G4_Si";
  const G4Material* theSi = G4NistManager::Instance()->FindOrBuildMaterial(matName);
  
  const G4Element* elC = new G4Element("Carbon", "C", 6., 12.01*g/mole);
  if (theSi != nullptr) {
    G4cout << theSi << G4endl;
  } else {
    G4cout << " nothing: " << matName << G4endl;
  }
  
  if (elC != nullptr) {
    G4cout << elC << G4endl;
  } else {
    G4cout << " nothing: " << matName << G4endl;
  }
  
  return 0;
}

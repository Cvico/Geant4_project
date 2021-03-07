
#ifndef MATERIALS_HH
#define MATERIALS_HH

#include "G4Material.hh"


class Materials { // inherit from G4Material
public:
    
    // == Constructors
    Materials();
    Materials(G4String matName);
    // == Default destructor
    virtual ~Materials();
    
    // == Useful Methods
    void checkIfExists(const G4Material * mat);
    void addMaterial(const G4String matName);
    void getListOfMaterials();
    
  
private:
    const G4String fMaterialName = "";
    std::vector<G4Material*> fListOfMaterials{}; // Vector to store used materials
  
};
#endif

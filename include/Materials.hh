
#ifndef MATERIALS_HH
#define MATERIALS_HH

#include "G4Material.hh"

class G4Material;
class Materials{ // inherit from G4Material
public:
    
    // =================================== //
    //      CONSTRUCTOR DECLARATION        //
    // =================================== //

    Materials();
    Materials(G4String matName); 
    Materials(G4String matName, G4String symbol, unsigned int z, float a);

    // =================================== //
    //      DESTRUCTOR DECLARATION         //
    // =================================== //
    virtual ~Materials();
    
    // =================================== //
    //          METHOD DECLARATION         //
    // =================================== //
    void checkIfExists(const G4Material * mat);
    void addMaterial(const G4String matName);
    void addMaterial(G4Material* mat);
    void getListOfMaterials();
    
  
private:
    const G4String fMaterialName = "";
    std::vector<G4Material*> fListOfMaterials{}; // Vector to store used materials
  
};
#endif

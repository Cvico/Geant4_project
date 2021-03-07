#include <iostream>
#include "DetectorConstruction.hh"
#include "Materials.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"

// -- Default constructor implementation
Materials::Materials(){
    // Initialize attributes
    std::cout << "[INFO]: DEFAULT CONSTRUCTOR FOR MATERIALS HAS BEEN CALLED" << std::endl;
    std::cout << " ---- Initializing the list of materials:" << std::endl;
    std::cout << " ---- Finished " << std::endl;
    

}
// Elaborated constructor implementation:
Materials::Materials(G4String matName){
    std::cout << "[INFO]: Creating materials..." << std::endl;
    std::cout << " ---- Initializing the list of materials:" << std::endl;
    addMaterial(matName);
    std::cout << " ---- Finished " << std::endl;
    
}

// -- Default destructor implementation
Materials::~Materials(){}


// -- Method implementation
void Materials::checkIfExists(const G4Material* mat){
    (mat != nullptr) ? G4cout << mat << G4endl : G4cout << mat << "is not defined..." << G4endl;
    return;
}

void Materials::addMaterial(const G4String matName){
    fListOfMaterials.push_back(G4NistManager::Instance()->FindOrBuildMaterial(matName));
}

void Materials::getListOfMaterials(){
    if (fListOfMaterials.size() == 0){std::cout << "No materials have been added yet." << std::endl;}
    else {
        for (long unsigned int mat_index = 0; mat_index < fListOfMaterials.size(); mat_index++){
            std::cout << "Material: " << fListOfMaterials.at(mat_index) << std::endl;
        }
    }   
}


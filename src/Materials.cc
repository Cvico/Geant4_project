#include <iostream>
#include "DetectorConstruction.hh"
#include "Materials.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"


// =================================== //
//      CONSTRUCTOR DEFINITION         //
// =================================== //

Materials::Materials(){
    // -- Default constructor implementation
    std::cout << "[INFO]: DEFAULT CONSTRUCTOR FOR MATERIALS HAS BEEN CALLED" << std::endl;
    std::cout << " ---- Initializing the list of materials:" << std::endl;
    std::cout << " ---- Finished " << std::endl;
    

}

Materials::Materials(G4String matName){
    // Constructor to search for already implemented materials
    // in the NIST database
    std::cout << "[INFO]: Creating materials..." << std::endl;
    std::cout << " ---- Initializing the list of materials:" << std::endl;

    addMaterial(matName);
    std::cout << " ---- Finished " << std::endl;
    
}

// =================================== //
//      DESTRUCTOR DEFINITION          //
// =================================== //
Materials::~Materials(){}


// =================================== //
//      METHOD DEFINITION              //
// =================================== //


// Methods that add new materials and elements to the list
void Materials::addMaterial(const G4String matName){
    // This method implements a way of implementing new
    // materials from the G4Nist database
    G4Material* mat = G4NistManager::Instance()->FindOrBuildMaterial(matName);
    addMaterial(mat);
}

void Materials::addMaterial(G4Material* mat){
    // This method simply adds an input material to the list
    // [FUTURE]: Try to implement overloaded methods
    // to avoid user material self-definition?
    fListOfMaterials.push_back(mat);    
}

void Materials::getListOfMaterials(){
    if (fListOfMaterials.size() == 0){
        std::cout 
        << "No materials have been added yet." 
        << std::endl;} else {
        for (long unsigned int mat_index = 0; mat_index < fListOfMaterials.size(); mat_index++){
            std::cout << "Material: " << fListOfMaterials.at(mat_index) << std::endl;
        }
    }   
}

void Materials::checkIfExists(const G4Material* mat){
    (mat != nullptr) ? G4cout << mat << G4endl : G4cout << mat << "is not defined..." << G4endl;
    return;
}
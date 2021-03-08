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
    checkIfExists(mat); // Check if the return is correct (i.e, it exists).
    addMaterial(mat);
}

void Materials::addMaterial(G4Material* mat){
    // This method simply adds an input material to the list
    // [FUTURE]: Try to implement overloaded methods
    // to avoid user material self-definition?
    checkIfExists(mat); // Check if it is a valid pointer.
    fListOfMaterials.push_back(mat);    
}

void Materials::addElement(G4Element* el){
    // This method simply adds an input material to the list
    // [FUTURE]: Try to implement overloaded methods
    // to avoid user material self-definition?
    checkIfExists(el); // Check if it is a valid pointer.
    fListOfElements.push_back(el);    
}

void Materials::addIsotope(G4Isotope* iso){
    // This method simply adds an input material to the list
    // [FUTURE]: Try to implement overloaded methods
    // to avoid user material self-definition?
    checkIfExists(iso); // Check if it is a valid pointer.
    fListOfIsotopes.push_back(iso);    
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

void Materials::getListOfElements(){
    if (fListOfElements.size() == 0){
        std::cout 
        << "No elements have been added yet." 
        << std::endl;} else {
        for (long unsigned int el_index = 0; el_index < fListOfElements.size(); el_index++){
            std::cout << "Element: " << fListOfElements.at(el_index) << std::endl;
        }
    }   
}

void Materials::getListOfIsotopes(){
    if (fListOfIsotopes.size() == 0){
        std::cout 
        << "No elements have been added yet." 
        << std::endl;} else {
        for (long unsigned int iso_index = 0; iso_index < fListOfIsotopes.size(); iso_index++){
            std::cout << "Isotope: " << fListOfIsotopes.at(iso_index) << std::endl;
        }
    }   
}

void Materials::checkIfExists(G4Material* mat){
    (mat != nullptr) ? G4cout << mat << G4endl : 
                       G4cout << mat << "is not defined..." << G4endl;
    return;
}

void Materials::checkIfExists(G4Element* el){
    (el != nullptr) ? G4cout << el << G4endl : 
                       G4cout << el << "is not defined..." << G4endl;
    return;
}

void Materials::checkIfExists(G4Isotope* iso){
    (iso != nullptr) ? G4cout << iso << G4endl : 
                       G4cout << iso << "is not defined..." << G4endl;
    return;
}
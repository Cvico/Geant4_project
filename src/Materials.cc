#include <iostream>
#include "G4Types.hh"
#include "globals.hh"
#include "G4RunManager.hh"
#include "G4PhysListFactory.hh"
#include "DetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "Materials.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
// =================================== //
//      CONSTRUCTOR DEFINITION         //
// =================================== //

Materials::Materials(){
    // -- Default constructor implementation
    // This can be improved using inheritance with 
    // each class constructor
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
    checkValidity(mat); // Check if the return is correct (i.e, it exists).
    addMaterial(mat);
}

void Materials::addMaterial(G4Material* mat){
    checkValidity(mat); // Check if it is a valid pointer.
    fListOfMaterials.push_back(mat);    
}

void Materials::addElement(G4Element* el){
    checkValidity(el); // Check if it is a valid pointer.
    fListOfElements.push_back(el);    
}

void Materials::addIsotope(G4Isotope* iso){
    checkValidity(iso); // Check if it is a valid pointer.
    fListOfIsotopes.push_back(iso);    
}


// Get methods
std::vector<G4Material*> Materials::getListOfMaterials(){
    return fListOfMaterials;
}
std::vector<G4Element*> Materials::getListOfElements(){
    return fListOfElements;
}
std::vector<G4Isotope*> Materials::getListOfIsotopes(){
    return fListOfIsotopes;
}

void Materials::printListOfMaterials(){
    printList(fListOfMaterials);
}

void Materials::printListOfElements(){
    printList(fListOfElements);
}

void Materials::printListOfIsotopes(){
    printList(fListOfIsotopes);   
}


// For getting information:
// ------------------------------------
template <typename G4obj>
void Materials::printList(std::vector<G4obj*> vec){
    if (vec.size() == 0){
        std::cout 
        << "No elements have been added yet." 
        << std::endl;} else {
        for (long unsigned int vec_index = 0; vec_index < vec.size(); vec_index++){
            std::cout << "Isotope: " << fListOfIsotopes.at(vec_index) << std::endl;
        }
    }
    
}

template <typename G4obj>
void Materials::checkValidity(G4obj* g4obj){
    (g4obj != nullptr) ? G4cout << g4obj << G4endl : 
                         G4cerr << g4obj << "is not a valid pointer..." << G4endl;
    return;
}

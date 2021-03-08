
#ifndef MATERIALS_HH
#define MATERIALS_HH

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"

class G4Material;
class G4Element;
class G4Isotope;


/*
    In this class we can store information about all the materials
    that can be used for constructing the materials of a certain detector.
    The G4Material class has an already implemented method to add certain
    materials to an already existing material, but with this class we can
    store information without having to add each material.

    Think of this class as a dictionary to store different materials, this
    can be useful to later build new materials from what is stored in a Materials
    object.
*/


class Materials{
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

    // For materials
    void addMaterial(const G4String matName);
    void addMaterial(G4Material* mat);
    void addElement(G4Element* el);
    void addIsotope(G4Isotope* iso);


    // Get methods
    std::vector<G4Material*> getListOfMaterials();
    std::vector<G4Element*> getListOfElements();
    std::vector<G4Isotope*> getListOfIsotopes();

    // Print listings
    void printListOfMaterials();
    void printListOfElements();
    void printListOfIsotopes();

    template <typename G4obj>
    void printList(std::vector<G4obj*> vec);
    template <typename G4obj>
    void checkValidity(G4obj* g4obj);

private:
    std::vector<G4Isotope*> fListOfIsotopes{};
    std::vector<G4Element*> fListOfElements{};
    std::vector<G4Material*> fListOfMaterials{}; // Vector to store used materials
  
};
#endif

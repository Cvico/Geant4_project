
#ifndef MATERIALS_HH
#define MATERIALS_HH

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"

class G4Material;
class G4Element;
class G4Isotope;


/**
    Think of this class as a dictionary to store different materials, this
    can be useful to later build new materials from what is stored in a Materials
    object.
*/


class Materials{
public:
    
    // =================================== //
    //      CONSTRUCTOR DECLARATION        //
    // =================================== //

    /**
     * @brief Default constructor
     */
    Materials();
    
    /**
     * @brief Constructor to get material from the NIST database
     * @param matName Name of the material to search for in the NIST db.
     */
    Materials(G4String matName); 
    /**
     * @brief Constructor for building custom materials
     * @param matName Name for the new material
     * @param symbol Symbol for the new material
     * @param z atomic number
     * @param a nuclear number
     */
    Materials(G4String matName, G4String symbol, unsigned int z, float a);

    /**
     * @brief Default destructor
     */
    virtual ~Materials();
    
    // =================================== //
    //          METHOD DECLARATION         //
    // =================================== //

    // For materials
    /**
     * @brief Adds the given material to the list of materials (fListOfMaterials)
     * @brief by searching for it in the NIST db.
     * @param matName name of the material to search for in the NIST db
     */
    void addMaterial(const G4String matName);
    /**
     * @brief Adds the given material to the list of materials
     * @param mat material to add
     */
    void addMaterial(G4Material* mat);
    /**
     * @brief Adds the given element to the list of elements.
     * @param el element to add
     */
    void addElement(G4Element* el);
    /**
     * @brief Adds the given isotope to the list of isotopes
     * @param iso isotope to add
     */
    void addIsotope(G4Isotope* iso);


    // Get methods
    /**
     * @brief Returns a pointer to the current listOfMaterials
     */
    std::vector<G4Material*> getListOfMaterials();
    /**
     * @brief Returns a pointer to the current listOfElements
     */
    std::vector<G4Element*> getListOfElements();
    /**
     * @brief Returns a pointer to the current listOfIsotopes
     */
    std::vector<G4Isotope*> getListOfIsotopes();

    // Print listings
    /**
     * @brief Prints the current listOfMaterials
     */
    void printListOfMaterials();
    /**
     * @brief Prints the current listOfElements
     */
    void printListOfElements();
    /**
     * @brief Prints the current listOfIsotopes
     */
    void printListOfIsotopes();
    
    /**
     * @brief Template function to print any kind of list given the object
     * @param G4obj An object of type G4Material, G4Element or G4Isotope
     */
    template <typename G4obj>
    void printList(std::vector<G4obj*> vec);
    /**
     * @brief Template function to check the validity (being validity -> not nullptr) of any kind of G4Object
     * @param G4obj An object of type G4Material, G4Element or G4Isotope
     */
    template <typename G4obj>
    void checkValidity(G4obj* g4obj);

private:
    std::vector<G4Isotope*> fListOfIsotopes{}; /**< List of stored isotopes */
    std::vector<G4Element*> fListOfElements{}; /**< List of stored elements */
    std::vector<G4Material*> fListOfMaterials{}; /**< List of stored materials */
  
};
#endif

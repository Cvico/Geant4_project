
#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "Materials.hh"
#include "DetectorMessenger.hh"
#include "G4Box.hh"
class G4Material;
class DetectorMessenger;

/**
 A User-defined class used for setting up the required attributes that define a detector. 
 This class inherits from G4VUserDetectorConstruction, whose documentation can be found at
 [ADD LINK TO THE DOCUMENTATION]
 */
class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  /**
  * @brief Default constructor
  * @return DetectorConstruction object
  */
  DetectorConstruction();
  /**
  * @brief Constructor for setting up the detector based on a certain material
  * @param mat material to add to the detector construction
  * @return DetectorConstruction object
  */
  DetectorConstruction(G4Material *mat);
  /**
  * @brief Constructor for setting up both the target material and the thickness of it.
  * @param mat material which makes up the target 
  * @param targetThickness thickness of the target
  * @return DetectorConstruction object
  */
  DetectorConstruction(G4Material *mat, G4double targetThickness);
  /**
  * @brief Destructor
  */
  ~DetectorConstruction();

  // Getters
  /**
  * @brief Returns the stored G4Box that builds up the solid world
  * @return G4Box
  */
  G4Box *GetTargetBox() { return fBox; }
  /**
  * @brief Returns the stored G4LogicalVolume that builds up the logical world
  * @return G4LogicalVolume
  */
  G4LogicalVolume *GetTargetLogicalVolume() { return fLogicalVolume; }
  /**
  * @brief Returns the stored G4PhysicalVolume that builds up the physical world
  * @return G4PhysicalVolume
  */
  G4VPhysicalVolume *GetTargetPhysicalVolume() { return fPhysicalVolume; }
  /**
  * @brief Returns the target material object
  * @return G4Material
  */
  G4Material *GetTargetMaterial() { return fTargetMaterial; };
  G4double GetTargetThickness() { return fTargetThickness; };
  G4double GetGunXPosition() { return fGunXPosition; };
  G4double GetGunYPosition() { return fGunYPosition; };
  G4double GetGunZPosition() { return fGunZPosition; };

  // Setters
  /**
  * @brief Sets the target material by performing fTargetMaterial = mat
  * @param mat Material to build the target
  * @return G4Material
  */
  void setTargetMaterial(G4Material* mat) { fTargetMaterial = mat; };
  void setTargetMaterial(G4String matName);
  void setTargetThickness(G4double targetThickness) { fTargetThickness = targetThickness; };
  void SetGunXPosition(G4double GunXPosition) { fGunXPosition = GunXPosition; };
  void SetGunYPosition(G4double GunYPosition) { fGunYPosition = GunYPosition; };
  void SetGunZPosition(G4double GunZPosition) { fGunZPosition = GunZPosition; };

  // methods to build solid world
  
  // Setters
  /**
  * @brief Builds the solid world for the detector. It has three overloaded methods:
  * @brief * no parameters passed: it takes default attributes
  * @brief * If a name is passed, then it takes default attributes and sets its name as the one passed
  * @brief * If a name and three position coordinates are passed, then also the the position for the solid world is set
  */
  void buildSolidWorld();
  void buildSolidWorld(G4String Name);
  void buildSolidWorld(G4String Name, G4double worldXsize, G4double worldYsize, G4double worldZsize);
  // methods to build logical world
  
  /**
  * @brief Sets the logical world. There are two overloaded methods:
  * @brief * If no parameter is passed, then the default attributes are used, see that documentation
  * @brief * If a name is passed, then world's name is set
  */
  void buildLogicalWorld();
  void buildLogicalWorld(G4String Name);
  // methods to build physical world
  /**
  * @brief Sets the Physical world. There are two overloaded methods:
  * @brief * If no parameter is passed, then the default attributes are used, see that documentation
  * @brief * If a name is passed, then world's name is set
  */
  void buildPhysicalWorld();
  void buildPhysicalWorld(G4String Name);

  // Method to finally build the detector
  virtual G4VPhysicalVolume *Construct();
  virtual G4VPhysicalVolume *Construct(G4String Name);
  virtual G4VPhysicalVolume *Construct(G4String Name, G4double worldXsize, G4double worldYsize, G4double worldZsize);

  void checkValidity(G4Material *mat);

private:
  G4Material *fTargetMaterial = nullptr;
  G4Box *fBox= nullptr;
  G4LogicalVolume *fLogicalVolume= nullptr;
  G4VPhysicalVolume *fPhysicalVolume= nullptr;
  G4double fTargetThickness= 1*CLHEP::m;

  G4double fWorldXsize = 1 * CLHEP::m;
  G4double fWorldYsize = 1 * CLHEP::m;
  G4double fWorldZsize = 1 * CLHEP::m;

  G4double fGunXPosition = 1 * CLHEP::m;
  G4double fGunYPosition = 1 * CLHEP::m;
  G4double fGunZPosition = 1 * CLHEP::m;

  DetectorMessenger* fDetMessenger= nullptr; 
};

#endif

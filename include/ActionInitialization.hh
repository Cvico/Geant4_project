#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH
#include "G4VUserActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"



/**
 * @brief This is the abstract base class for instantiating all the user action classes. 
 * @brief It has a pure virtual method Build() which is invoked by G4RunManager for sequential execution 
 * @brief and G4WorkerRunManager for multi-threaded execution. The additional virtual method BuildForMaster() 
 * @brief will be invoked from G4MTRunManager for multi-threaded execution.
 */
class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    ActionInitialization(DetectorConstruction* detector);
    virtual ~ActionInitialization(){};

    virtual void Build() const;

private:
    DetectorConstruction *fDetector = nullptr;


};

#endif
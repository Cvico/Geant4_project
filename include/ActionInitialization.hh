#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH
#include "G4VUserActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "CalorimeterConstruction.hh"


class DetectorConstruction;

class ActionInitialization : public G4VUserActionInitialization {
public:
    ActionInitialization();
    ActionInitialization(DetectorConstruction* detector);
    virtual ~ActionInitialization(){};

    virtual void Build() const;
    virtual void BuildForMaster() const; // Only use in multithread mode.

private:
    DetectorConstruction*fDetector;


};

#endif

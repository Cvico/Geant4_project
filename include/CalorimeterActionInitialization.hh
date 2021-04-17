#ifndef CALORIMETERACTIONINITIALIZATION_HH
#define CALORIMETERACTIONINITIALIZATION_HH
#include "G4VUserActionInitialization.hh"
#include "CalorimeterPrimaryGeneratorAction.hh"
#include "CalorimeterConstruction.hh"


class CalorimeterConstruction;

class CalorimeterActionInitialization : public G4VUserActionInitialization {
public:
    CalorimeterActionInitialization();
    virtual ~CalorimeterActionInitialization(){};

    virtual void Build() const;
    virtual void BuildForMaster() const; // Only use in multithread mode.

private:
    CalorimeterConstruction* fDetector;


};

#endif

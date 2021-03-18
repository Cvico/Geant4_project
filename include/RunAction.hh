#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"

#include "G4String.hh"

// forward declarations
class PrimaryGeneratorAction;
class G4Run;


class RunAction : public G4UserRunAction {

  // Method declaration:
  public:
    
    // CTR: 
    //  - detector construction object is used in the stepping action to check target
    //  - primary generator is used to re-set position for workers and to get E0 (set only for workers)
    RunAction(PrimaryGeneratorAction* prim = nullptr);
    virtual ~RunAction();

    // Virtual method that is called by the RunManager before the first event starts
    virtual void   BeginOfRunAction(const G4Run*);

    // Virtual method that is called by the RunManager after the last event finished
    virtual void   EndOfRunAction(const G4Run*);

  // Data member declarations:
  private:

  	PrimaryGeneratorAction*  fPrimary = nullptr;     
};

#endif
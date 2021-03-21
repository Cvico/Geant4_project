#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"

#include "G4String.hh"

// forward declarations
class PrimaryGeneratorAction;
class G4Run;

/**
* @brief It accumulates statistics and computes dispersion 
* @brief of the energy deposit and track lengths of charged 
* @brief particles with the aid of analysis tools. H1D 
* @brief histograms are created in BeginOfRunAction() 
* @brief for the energy deposit and track length in both Absorber 
* @brief and Gap volumes. The same values are also saved in an ntuple.
* @brief The histograms and ntuple are saved in the output file in a 
* @brief format according to a selected technology in B4Analysis.hh.
* @brief In EndOfRunAction(), the accumulated statistics and computed
* @brief dispersion are printed. When running in multi-threading mode, 
* @brief the histograms accumulated on threads are automatically merged
* @brief in a single output file, while the ntuple is written in files per thread.
*/

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

  	PrimaryGeneratorAction*  fPrimary;     
};

#endif
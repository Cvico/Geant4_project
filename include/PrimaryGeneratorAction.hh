#ifndef PRIMARYGENERATORACTION_HH
#define PRIMARYGENERATORACTION_HH

#include "PrimaryGeneratorAction.hh"
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
#include "G4VUserPrimaryGeneratorAction.hh"

class DetectorConstruction;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction(DetectorConstruction* det);
    ~PrimaryGeneratorAction();

    void createParticleGun();
    void generateParticle();

    // Getters
    G4ParticleGun* GetParticleGun() { return fParticleGun;};
    const G4String& GetParticleName();

    // Setters
    void SetKinematics();
    void UpdatePosition();
    virtual void GeneratePrimaries(G4Event* anEvent);
private:
    G4ParticleGun* fParticleGun;
    DetectorConstruction* fDetector;
};

#endif
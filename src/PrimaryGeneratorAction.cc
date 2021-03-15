#include "PrimaryGeneratorAction.hh"

#include "DetectorConstruction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh" 
#include "G4ParticleTable.hh"
#include <math.h>

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* det){
    // create the particle-gun object
    fDetector    = det;
    fParticleGun = new G4ParticleGun();
    SetDefaultKinematic();
}


PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}


void PrimaryGeneratorAction::GeneratePrimaries(G4Event* evt) {
	fParticleGun->GeneratePrimaryVertex(evt);
}


void PrimaryGeneratorAction::SetDefaultKinematic() {
//
// default primary particle: 30 [MeV] e- perpendicular to the target
   UpdateDefinition("e-");
   UpdateMomentumDirection( G4ThreeVector(1., 0., 0.) );
   UpdateEnergy( 30.*CLHEP::MeV );
   UpdateMomentum(fParticleGun->GetParticleMomentum());
   UpdateNumberOfParticles(1);
   UpdatePosition();
}


// needs to be invoked for all workers at the begining of the run: user might 
// have changed the target thickness
void PrimaryGeneratorAction::UpdateDefinition(G4String partname){
   G4ParticleDefinition* part = G4ParticleTable::GetParticleTable()->FindParticle( partname );
   fParticleGun->SetParticleDefinition( part );
}
void PrimaryGeneratorAction::UpdatePosition() {
    fParticleGun->SetParticlePosition( 
        G4ThreeVector( fDetector->GetGunXPosition(), fDetector->GetGunYPosition(), fDetector->GetGunZPosition() ) );
}

void PrimaryGeneratorAction::UpdateMomentum(G4double momentum) {
    fParticleGun->SetParticleMomentum(momentum);
}

void PrimaryGeneratorAction::UpdateMomentumDirection(G4ThreeVector momentumDir) {
    fParticleGun->SetParticleMomentumDirection(momentumDir);
}

void PrimaryGeneratorAction::UpdateNumberOfParticles(G4int nparticles){
    fParticleGun->SetNumberOfParticles(nparticles);
}

void PrimaryGeneratorAction::UpdateEnergy(G4double partEnergy){
    fParticleGun->SetNumberOfParticles(partEnergy);
}

const G4String& PrimaryGeneratorAction::GetParticleName() const {
	return fParticleGun->GetParticleDefinition()->GetParticleName();
}


G4double PrimaryGeneratorAction::GetParticleEnergy() const {
	return fParticleGun->GetParticleEnergy();
}


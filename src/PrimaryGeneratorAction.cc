#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "G4ParticleGun.hh"
#include "G4Electron.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction* det){
    fDetector = det;
    createParticleGun();
    generateParticle();
}

void PrimaryGeneratorAction::createParticleGun(){
    // Default particleGun creation
    fParticleGun = new G4ParticleGun(1);
    return;
}

void PrimaryGeneratorAction::SetKinematics(){
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(1.0, 0.0, 0.0));
    return;
}

void PrimaryGeneratorAction::UpdatePosition(){
    // Default Particle Position
    fParticleGun->SetParticlePosition(G4ThreeVector(fDetector->GetGunXPosition(), 0.0, 0.0));
    return;
}
void PrimaryGeneratorAction::generateParticle(){
    // Default particle generation
    G4ParticleDefinition* part = G4Electron::Definition();
    fParticleGun->SetParticleDefinition(part);
    SetKinematics();
    UpdatePosition();
    fParticleGun->SetParticleEnergy(30.0*CLHEP::MeV);
    return;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent){return;}
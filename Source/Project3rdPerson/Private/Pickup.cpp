

#include "Project3rdPerson.h"

#include "Pickup.h"


APickup::APickup(const class FPostConstructInitializeProperties& PCIP) :
    Super(PCIP),
    IsActive(true)
{
    BaseCollisionComponent = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("BaseSphereComponent")) ;

    RootComponent = BaseCollisionComponent ;

    PickupMesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("PickupMesh")) ;

    PickupMesh->SetSimulatePhysics(true) ;

    PickupMesh->AttachTo(RootComponent) ;
}

void APickup::onPickedUp_Implementation() {
    //nothing here
}

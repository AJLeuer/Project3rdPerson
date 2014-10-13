

#include "Project3rdPerson.h"

#include "BatteryPickup.h"


ABatteryPickup::ABatteryPickup(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP)
{
    // The base power level of the battery.
    PowerLevel = 150.f;
}

void ABatteryPickup::onPickedUp_Implementation()
{
    // Call the parent implementation of OnPickedUp first.
    Super::onPickedUp_Implementation();
    // Destroy the battery
    Destroy();
}


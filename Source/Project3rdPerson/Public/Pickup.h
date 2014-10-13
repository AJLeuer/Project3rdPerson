

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

/**
 *
 */
UCLASS()
class PROJECT3RDPERSON_API APickup : public AActor
{
	GENERATED_UCLASS_BODY()

public:

    /** True when the pickup is able to be picked up, false if something deactivates the pickup. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
    bool IsActive;
    
    /** Simple collision primitive to use as the root component. */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
    TSubobjectPtr<USphereComponent> BaseCollisionComponent;
    
    /** StaticMeshComponent to represent the pickup in the level. */
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
    TSubobjectPtr<UStaticMeshComponent> PickupMesh;
    
    /** Function to call when the Pickup is collected. */
    UFUNCTION(BlueprintNativeEvent)
    void onPickedUp() ;

};

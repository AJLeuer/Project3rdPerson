// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameObject.h"

#include "GameFramework/Character.h"
#include "Project3rdPersonCharacter.generated.h"

UCLASS(config=Game)
class AProject3rdPersonCharacter : public ACharacter, public GameObject
{
	GENERATED_UCLASS_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	TSubobjectPtr<class UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
	TSubobjectPtr<class USphereComponent> CollectionSphere ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Power)
	float PowerLevel ;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Power)
	float SpeedFactor ;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Power)
	float BaseSpeed ;

	virtual void Tick(float deltaSeconds) override ;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	UFUNCTION(BlueprintCallable, Category = Power)
	void collectBatteries() ;

	UFUNCTION(BlueprintImplementableEvent, category = Power)
	void powerUp(float Energy) ;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
};

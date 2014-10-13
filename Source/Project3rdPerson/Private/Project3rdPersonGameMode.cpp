// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Project3rdPerson.h"

#include "Project3rdPersonGameMode.h"
#include "Project3rdPersonCharacter.h"

AProject3rdPersonGameMode::AProject3rdPersonGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEFieldTestTPGameMode.h"
#include "UEFieldTestTPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUEFieldTestTPGameMode::AUEFieldTestTPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

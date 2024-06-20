// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeBase_PawnMovement.generated.h"

/**
 * 
 */
UCLASS()
class UEFIELDTESTTP_API AGameModeBase_PawnMovement : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameModeBase_PawnMovement();

protected:
	virtual void BeginPlay() override;

public:
	APawn* ControlledCube;
	APawn* ControlledSphere;
	APawn* CurrentControlledPawn;

	void InitializePawns();
};

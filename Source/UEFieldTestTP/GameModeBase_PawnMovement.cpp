// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase_PawnMovement.h"

#include "PawnCube.h"
#include "PawnSphere.h"
#include "Kismet/GameplayStatics.h"

AGameModeBase_PawnMovement::AGameModeBase_PawnMovement()
{
	DefaultPawnClass = nullptr;
}

void AGameModeBase_PawnMovement::BeginPlay()
{
	Super::BeginPlay();

	InitializePawns();
}

void AGameModeBase_PawnMovement::InitializePawns()
{
	// Declare an array of actors to store the found pawns
	TArray<AActor*> FoundPawns;

	// Get the cueb pawn
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnCube::StaticClass(), FoundPawns);
	if (FoundPawns.Num() > 0)
	{
		ControlledCube = Cast<APawn>(FoundPawns[0]);
	}

	// Empty the array and get the sphere pawn
	FoundPawns.Empty();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnSphere::StaticClass(), FoundPawns);
	if (FoundPawns.Num() > 0)
	{
		ControlledSphere = Cast<APawn>(FoundPawns[0]);
	}

	// Possess the initial pawn (cube) and set the camera
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		CurrentControlledPawn = ControlledCube;
		PlayerController->Possess(ControlledCube);
		PlayerController->SetViewTargetWithBlend(CurrentControlledPawn);
	}
}

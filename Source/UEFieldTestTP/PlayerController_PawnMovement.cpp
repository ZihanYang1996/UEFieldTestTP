// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_PawnMovement.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "PawnSphere.h"
#include "PawnCube.h"
#include "DefaultInputSystem/MyGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameModeBase_PawnMovement.h"

void APlayerController_PawnMovement::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	if (AGameModeBase_PawnMovement* GameMode = Cast<AGameModeBase_PawnMovement>(
		UGameplayStatics::GetGameMode(GetWorld())))
	{
		ControlledCube = GameMode->GetControlledCube();
		ControlledSphere = GameMode->GetControlledSphere();
		CurrentControleldPawn = GameMode->GetCurrentControlledPawn();
	}

	// Get the pawn controlled by the player
	// CurrentControleldPawn = GetPawn();
}

void APlayerController_PawnMovement::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
		                                   &APlayerController_PawnMovement::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerController_PawnMovement::Look);
		EnhancedInputComponent->BindAction(SwitchPawnAction, ETriggerEvent::Completed, this,
		                                   &APlayerController_PawnMovement::SwitchPawn);
	}
}

void APlayerController_PawnMovement::Move(const FInputActionValue& Value)
{
	if (CurrentControleldPawn->IsA(APawnCube::StaticClass()))
	{
		Cast<APawnCube>(CurrentControleldPawn)->Move(Value);
	}
	else if (CurrentControleldPawn->IsA(APawnSphere::StaticClass()))
	{
		Cast<APawnSphere>(CurrentControleldPawn)->Move(Value);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No pawn to move!"));
	}
	
}

void APlayerController_PawnMovement::SwitchPawn(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Switching pawn!"));
	if (CurrentControleldPawn == ControlledCube)
	{
		CurrentControleldPawn = ControlledSphere;
	}
	else if (CurrentControleldPawn == ControlledSphere)
	{
		CurrentControleldPawn = ControlledCube;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No pawn to switch to!"));
	}

	Possess(CurrentControleldPawn);
	SetViewTargetWithBlend(CurrentControleldPawn);
}

void APlayerController_PawnMovement::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();
	AddYawInput(LookInput.X);
	AddPitchInput(LookInput.Y);
}

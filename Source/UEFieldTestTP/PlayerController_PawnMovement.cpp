// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController_PawnMovement.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "PawnSphere.h"

void APlayerController_PawnMovement::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	// Get the pawn controlled by the player
	CurrentControleldPawn = GetPawn();
}

void APlayerController_PawnMovement::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerController_PawnMovement::Move);
		// EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerController_PawnMovement::Look);
		// EnhancedInputComponent->BindAction(SwitchPawnAction, ETriggerEvent::Triggered, this, &APlayerController_PawnMovement::SwitchPawn);
	}
}

void APlayerController_PawnMovement::Move(const FInputActionValue& Value)
{
	Cast<APawnSphere>(CurrentControleldPawn)->Move(Value);
}

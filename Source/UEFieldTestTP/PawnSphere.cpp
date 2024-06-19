// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnSphere.h"
#include "EnhancedInputComponent.h"

// Sets default values
APawnSphere::APawnSphere()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APawnSphere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnSphere::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawnSphere::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	// Print the value on the screen
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Move Value: %s"), *MovementVector.ToString()));
	}
}

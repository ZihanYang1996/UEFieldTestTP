// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingCube.h"

// Sets default values
AMovingCube::AMovingCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube Mesh"));
	RootComponent = CubeMesh;

}

// Called when the game starts or when spawned
void AMovingCube::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
	EndLocation = StartLocation + RelativeEndLocation;
}

// Called every frame
void AMovingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Calculate new location
	FVector CurrenLocation = GetActorLocation();
	FVector TargetLocation = bIsMovingToEnd ? EndLocation : StartLocation;
	FVector Direction = (TargetLocation - CurrenLocation).GetSafeNormal();
	FVector NewLocation = CurrenLocation + Direction * MoveSpeed * DeltaTime;

	// Move the actor
	SetActorLocation(NewLocation);

	// If the actor has reached the target location, switch direction
	if (FVector::DistSquared(NewLocation, TargetLocation) < 1.0f)
	{
		bIsMovingToEnd = !bIsMovingToEnd;
	}
}


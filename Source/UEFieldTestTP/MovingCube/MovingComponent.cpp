// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingComponent.h"

// Sets default values for this component's properties
UMovingComponent::UMovingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UMovingComponent::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetOwner()->GetActorLocation();
	EndLocation = StartLocation + RelativeEndLocation;
}


// Called every frame
void UMovingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (AActor* Owner = GetOwner())
	{
		// Calculate new location
		FVector CurrentLocation = Owner->GetActorLocation();
		FVector TargetLocation = bIsMovingToEnd ? EndLocation : StartLocation;
		FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		FVector NewLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;

		// Move the actor
		Owner->SetActorLocation(NewLocation);
		
		// If the actor has reached the target location, switch direction
		if (FVector::DistSquared(NewLocation, TargetLocation) < 1.0f)
		{
			bIsMovingToEnd = !bIsMovingToEnd;
		}
	}
}


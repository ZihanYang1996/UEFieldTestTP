// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UEFIELDTESTTP_API UMovingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMovingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere, Category="Moving Component", meta=(AllowPrivateAccess="true"))
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category="Moving Component", meta=(AllowPrivateAccess="true"))
	FVector RelativeEndLocation = FVector(1000.0f, 0.0f, 0.0f);

	FVector StartLocation;
	FVector EndLocation;
	bool bIsMovingToEnd = false;  // Is the cube currently moving to the end location?
		
};

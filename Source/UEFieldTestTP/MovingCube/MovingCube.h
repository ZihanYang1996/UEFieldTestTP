// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingCube.generated.h"

UCLASS()
class UEFIELDTESTTP_API AMovingCube : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditAnywhere, Category="Moving Component", meta=(AllowPrivateAccess="true"))
	float MoveSpeed = 100.0f;

	UPROPERTY(EditAnywhere, Category="Moving Component", meta=(AllowPrivateAccess="true"))
	FVector RelativeEndLocation = FVector(1000.0f, 0.0f, 0.0f);

	FVector StartLocation;
	FVector EndLocation;
	bool bIsMovingToEnd = false;  // Is the cube currently moving to the end location?
	
public:	
	// Sets default values for this actor's properties
	AMovingCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnSphere.generated.h"

class USpringArmComponent;
struct FInputActionValue;
class UCameraComponent;

UCLASS()
class UEFIELDTESTTP_API APawnSphere : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnSphere();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);

	UCameraComponent* GetCameraComponent() const { return Camera; }

private:
	// Static Mesh Component
	UPROPERTY(EditAnywhere, Category="Input")
	UStaticMeshComponent* SphereMesh;

	// Movement variables
	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed = 500.0f;

	// Camera Component
	UPROPERTY(EditAnywhere, Category="Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, Category="Camera")
	UCameraComponent* Camera;

};

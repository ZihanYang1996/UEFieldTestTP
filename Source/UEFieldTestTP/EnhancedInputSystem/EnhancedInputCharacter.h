// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputCharacter.generated.h"

UCLASS()
class UEFIELDTESTTP_API AEnhancedInputCharacter : public ACharacter
{
	GENERATED_BODY()

	// Movement & Look	
	/** Mapping Context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enhanced Input System", meta=(AllowPrivateAccess="true"))
	class UInputMappingContext* InputMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enhanced Input System", meta=(AllowPrivateAccess="true"))
	class UInputAction* IA_Move;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enhanced Input System", meta=(AllowPrivateAccess="true"))
	class UInputAction* IA_Look;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enhanced Input System", meta=(AllowPrivateAccess="true"))
	class UInputAction* IA_Jump;

	/** Turn Rate Horizontal */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseTurnRate;

	/** Turn Rate Vertical */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	float BaseLookUpRate;

	// Camera
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Customization", meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera Customization", meta=(AllowPrivateAccess="true"))
	class UCameraComponent* FollowCamera;

	// Overlap Capsule
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Overlap Detection", meta=(AllowPrivateAccess="true"))
	UCapsuleComponent* OverlapCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Overlap Detection", meta=(AllowPrivateAccess="true"))
	int32 NumOverlapping = false;

public:
	// Sets default values for this character's properties
	AEnhancedInputCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void Jump() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);


	// A function to move the character forward and backward just a tiny bit to make sure character can be pushed
	void ShakeCharacter();
};

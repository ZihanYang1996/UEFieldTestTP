// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnCube.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APawnCube::APawnCube()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set static mesh component
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	RootComponent = CubeMesh;

	// Create the spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	// Create the camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	bUseControllerRotationYaw = false; // Ensure the pawn uses the controller's yaw rotation
}

// Called when the game starts or when spawned
void APawnCube::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APawnCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APawnCube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APawnCube::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	// Print the value on the screen
	// if (GEngine)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
	// 	                                 FString::Printf(TEXT("Cube move Value: %s"), *MovementVector.ToString()));
	// }

	FRotator ControllerRoataionYaw(0, GetControlRotation().Yaw, 0);
	FVector ForwardVector = FRotationMatrix(ControllerRoataionYaw).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(ControllerRoataionYaw).GetUnitAxis(EAxis::Y);
	
	
	FVector ScaledDirection = ForwardVector * MovementVector.Y + RightVector * MovementVector.X;
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	AddActorWorldOffset(ScaledDirection * MoveSpeed * DeltaTime, true);
	
	// Rotate the cube
	FRotator TargetRotation = ScaledDirection.Rotation();
	// Smoothly rotate the cube
	FRotator NewRotation = FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, DeltaTime, RotateSpeed);
	SetActorRotation(NewRotation);
}

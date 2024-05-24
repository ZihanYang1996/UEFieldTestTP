// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedInputCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UEFieldTestTP/UEFieldTestTPCharacter.h"
#include "UEFieldTestTP/MovingCube/MovingComponent.h"
#include "WorldPartition/ContentBundle/ContentBundleLog.h"

// Sets default values
AEnhancedInputCharacter::AEnhancedInputCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set size for default collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 100.0f);

	// Create slightly larger capsule to detect overlap
	OverlapCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("OverlapCapsule"));
	OverlapCapsule->InitCapsuleSize(50.0f, 105.0f);
	OverlapCapsule->SetupAttachment(RootComponent);

	// Don't rotate when the controller rotates. Let that just affect the camera. (Try setting these to true and see what happens)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// bUseControllerRotationPitch = true;
	// bUseControllerRotationYaw = true;
	// bUseControllerRotationRoll = true;

	// Configure character movement (Try setting these to different values and see what happens)
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	// GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = true;
	// Rotate the arm based on the controller (Try setting this to false and see what happens)

	//Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false;
	// Camera does not rotate relative to arm (Try setting this to false and see what happens)

	// Will try to set skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) in the derived blueprint asset

	// For Overlap Detection
	// Bind the OnHit function to the overlap capsule component's Overlap event
	OverlapCapsule->OnComponentBeginOverlap.AddDynamic(
		this, &AEnhancedInputCharacter::AEnhancedInputCharacter::OnOverlapBegin);
	OverlapCapsule->OnComponentEndOverlap.AddDynamic(this, &AEnhancedInputCharacter::OnOverlapEnd);
	// Enable collision notifications
	OverlapCapsule->SetGenerateOverlapEvents(true);
	OverlapCapsule->BodyInstance.SetCollisionProfileName(TEXT("Pawn"));
}

// Called when the game starts or when spawned
void AEnhancedInputCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnhancedInputCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Shake the character if overlapping so it can be pushed out of the way
	ShakeCharacter();
}

// Input

// Called to bind functionality to input
void AEnhancedInputCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	// Cast the PlayerInputComponent to APlayerController
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0); // Add the InputMappingContext to the subsystem
		}
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);  // Bind the Jump action
		// EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);  // Bind the StopJumping action
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Started, this, &AEnhancedInputCharacter::Jump);
		// Bind the Jump action
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		// Bind the StopJumping action

		// Moving
		EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AEnhancedInputCharacter::Move);
		// Bind the Move action

		// Looking
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AEnhancedInputCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component!"),
		       *GetNameSafe(this));
	}
}

void AEnhancedInputCharacter::Jump()
{
	Super::Jump();
	// Just playing around with overriding
	// UE_LOG(LogTemp, Warning, TEXT("Jumping!"));
}

void AEnhancedInputCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AEnhancedInputCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X * BaseTurnRate * GetWorld()->GetDeltaSeconds());
		AddControllerPitchInput(LookAxisVector.Y * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}

void AEnhancedInputCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                             const FHitResult& SweepResult)
{
	if (OtherActor == this)
	{
		return;
	}
	// Print out the name of the actor that was hit
	// UE_LOG(LogTemplateCharacter, Warning, TEXT("Overlap Begin with: %s"), *OtherActor->GetActorLabel());
	NumOverlapping += 1;
}

void AEnhancedInputCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Print out the name of the actor that was hit
	// UE_LOG(LogTemplateCharacter, Warning, TEXT("End Overlap: %s"), *OtherActor->GetActorLabel());
	NumOverlapping -= NumOverlapping > 0 ? 1 : 0;
}

void AEnhancedInputCharacter::ShakeCharacter()
{
	if (NumOverlapping == 0)
	{
		return;
	}

	FHitResult HitResult;
	bool bMoved = GetMovementComponent()->MoveUpdatedComponent(FVector(2.0f, 0.0f, 0.0f),
	                                                           GetMovementComponent()->UpdatedComponent->
	                                                           GetComponentRotation(), true, &HitResult,
	                                                           ETeleportType::None);
	// if (bMoved)
	// {
	// 	UE_LOG(LogTemplateCharacter, Warning, TEXT("Moved Character"));
	// }

	bMoved = GetMovementComponent()->MoveUpdatedComponent(FVector(-2.0f, 0.0f, 0.0f),
	                                                      GetMovementComponent()->UpdatedComponent->
	                                                      GetComponentRotation(), true, &HitResult,
	                                                      ETeleportType::None);
	// if (bMoved)
	// {
	// 	UE_LOG(LogTemplateCharacter, Warning, TEXT("Moved Character Back"));
	// }
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnCube.h"

// Sets default values
APawnCube::APawnCube()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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


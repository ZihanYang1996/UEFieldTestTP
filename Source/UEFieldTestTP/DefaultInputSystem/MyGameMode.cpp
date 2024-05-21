// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "MyCharacter.h"

AMyGameMode::AMyGameMode()
{
	// Set default pawn class to our Blueprinted character
	DefaultPawnClass = AMyCharacter::StaticClass();
}



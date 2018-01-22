// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSCharacter.h"
#include "PSFPSPlayerController.h"
#include "PSGameMode.h"

APSGameMode::APSGameMode(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

	//Set the Default Pawn class to be ProjectSatomiCharacter
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/ProjectSatomi/PSCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerControllerClass = APSFPSPlayerController::StaticClass();

}

void APSGameMode::StartPlay()
{
	Super::StartPlay();

	StartMatch();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("HELLO WORLD"));
	}
}



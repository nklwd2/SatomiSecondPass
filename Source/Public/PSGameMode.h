// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "PSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSATOMI_API APSGameMode : public AGameMode
{
	GENERATED_BODY()

	APSGameMode(const FObjectInitializer& ObjectInitializer);


	virtual void StartPlay() override;
	
	
};

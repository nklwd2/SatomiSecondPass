// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PSWeaponState.h"
#include "PSWeaponFeedingState.generated.h"

/**
 * 
 */
UCLASS(CustomConstructor)
class PROJECTSATOMI_API UPSWeaponFeedingState : public UPSWeaponState
{
	GENERATED_UCLASS_BODY()

	UPSWeaponFeedingState(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
	{}

	void beginState(const UPSWeaponState* previousState) override;
	
	
};

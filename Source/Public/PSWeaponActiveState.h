// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PSWeaponState.h"
#include "PSWeaponActiveState.generated.h"

/**
 * 
 */
UCLASS(CustomConstructor)
class PROJECTSATOMI_API UPSWeaponActiveState : public UPSWeaponState
{
	GENERATED_UCLASS_BODY()

	UPSWeaponActiveState(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
	{}

	virtual void triggerPulled(const uint8 fireModeNum) override;
	
	
};

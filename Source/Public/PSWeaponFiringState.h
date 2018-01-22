// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PSWeaponState.h"
#include "PSWeaponFiringState.generated.h"

/**
 * 
 */
UCLASS(CustomConstructor)
class PROJECTSATOMI_API UPSWeaponFiringState : public UPSWeaponState
{
	GENERATED_UCLASS_BODY()
	
	UPSWeaponFiringState(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
	{}
	
	FTimerHandle checkIfTriggerIsStillPulledHandle;

	virtual void beginState(const UPSWeaponState* previousState) override;

	virtual void fire();

	virtual void checkIfTriggerIsStillPulled();
	
};

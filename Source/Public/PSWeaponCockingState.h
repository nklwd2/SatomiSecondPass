// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PSWeaponState.h"
#include "PSWeaponCockingState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSATOMI_API UPSWeaponCockingState : public UPSWeaponState
{
	GENERATED_UCLASS_BODY()

	void beginState(const UPSWeaponState* previousState) override;

	
};

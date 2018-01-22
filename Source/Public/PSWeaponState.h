// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PSWeaponState.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, CustomConstructor, Within=PSWeapon)
class PROJECTSATOMI_API UPSWeaponState : public UObject
{
	GENERATED_UCLASS_BODY()
	
	UPSWeaponState::UPSWeaponState(const FObjectInitializer& ObjectInitializer) : Super( ObjectInitializer){}

	virtual void beginState(const UPSWeaponState* previousState){}

	virtual void endState(){}

	/*virtual bool BeginFiringSequence() { return false; }

	virtual void EndFiringSequence(){}

	virtual bool IsFiring() const { return false;}

	virtual void UpdateTiming(){}

	virtual void Tick(float deltaT){}*/
	
	virtual void triggerPulled(const uint8 fireModeNum){
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("WeaponState Default implementation of TriggerPulled()"));
		}
	}

	virtual void AmmoEjectorActivated() {
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("WeaponState Default implementation of AmmoEjectorActivated()"));
		}
	}
	
};

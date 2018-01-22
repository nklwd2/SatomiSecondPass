// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSWeapon.h"
#include "PSWeaponCockingState.h"

UPSWeaponCockingState::UPSWeaponCockingState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UPSWeaponCockingState::beginState(const UPSWeaponState* previousState) {
	
	/* Play Firing Animation */

	/* Eject spent round from Weapon */

	/* Set firing hammer to engaged */
	GetOuterAPSWeapon()->isHammerEngaged = true;
	/* Bolt Flies backwards */
	GetOuterAPSWeapon()->isBoltForward = false;

	/* Transition to the feeding i.e the "rebound" of the bolt cause by firing */
	GetOuterAPSWeapon()->goToState(GetOuterAPSWeapon()->weaponStates.feedingState);
}


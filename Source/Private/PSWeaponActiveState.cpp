// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSWeapon.h"
#include "PSWeaponActiveState.h"


void UPSWeaponActiveState::triggerPulled(const uint8 fireModeNum) {


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("WeaponActiveState implementation of TriggerPulled()"));
	}

	/* Check if round is in chamber and hammer is engaged */
	if (GetOuterAPSWeapon()->isHammerEngaged) {
		if (GetOuterAPSWeapon()->weaponChamberState == EWeaponChamberState::ROUND_CHAMBERED) {
			/* Start Firing State */
			GetOuterAPSWeapon()->currentFireModeNum = fireModeNum;
			GetOuterAPSWeapon()->goToState(GetOuterAPSWeapon()->weaponStates.firingState);
		}
		else {
			/* Play the sound of hammer dry-firing*/
			GetOuterAPSWeapon()->dryFire();
		}
	}else {
		//Nothing happens besides trigger being pulled
	}

}
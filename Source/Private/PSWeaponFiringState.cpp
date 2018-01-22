// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSWeapon.h"
#include "PSWeaponFiringState.h"

void UPSWeaponFiringState::beginState(const UPSWeaponState * previousState){

	//Set a timer to check if the weapon should fire again due to player still holding trigger down
	GetOuterAPSWeapon()->GetWorldTimerManager().SetTimer(checkIfTriggerIsStillPulledHandle, this, &UPSWeaponFiringState::checkIfTriggerIsStillPulled, GetOuterAPSWeapon()->getTimeBetweenShots(GetOuterAPSWeapon()->currentFireModeNum), true);

	//Toggle firing sounds

	//Fire Weapon
	fire();

	/* Transition to the cocking or "Blowback" stage of firing */
	GetOuterAPSWeapon()->goToState(GetOuterAPSWeapon()->weaponStates.cockingState);

}

void UPSWeaponFiringState::fire(){
	GetOuterAPSWeapon()->fire();
}

void UPSWeaponFiringState::checkIfTriggerIsStillPulled(){

	if (GEngine){
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT("WeaponFiringState implementation of checkIfTriggerIsStillPulled()"));
	}

	/* Check if there are any reasons to completely halt firing*/

	/* Check if the weapon should continue firing */
	//TODO implement this checking, currently we have a bug due to this

	/* Fire Weapon */


}

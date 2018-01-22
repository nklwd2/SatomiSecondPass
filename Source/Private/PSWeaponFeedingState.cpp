// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSWeapon.h"
#include "AmmoClipSystemComponent.h"
#include "PSWeaponFeedingState.h"


void UPSWeaponFeedingState::beginState(const UPSWeaponState* previousState) {
	
	/* Take the round out of the magazine */
	if( GetOuterAPSWeapon()->weaponChamberState == EWeaponChamberState::SPENT_ROUND_CHAMBERED){
		//Play Ejection Animation TODO potentially move this into the firing weapon animation
	}

	GetOuterAPSWeapon()->weaponChamberState = EWeaponChamberState::EMTPY;

	/* Check if there is still a round left in the magazine*/
	if(GetOuterAPSWeapon()->ammoSystemComponent->tryConsumeAmmo()) {
		
		verifySlow(GetOuterAPSWeapon()->weaponChamberState == EWeaponChamberState::EMTPY);
		verifySlow(GetOuterAPSWeapon()->isBoltForward == false);
		verifySlow(GetOuterAPSWeapon()->ammoSystemComponent->canConsumeAmmo() == false);

		/* Chamber the round in the barrel of the weapon */
		GetOuterAPSWeapon()->weaponChamberState = EWeaponChamberState::ROUND_CHAMBERED;

		/* Bolt of the weapon flies forward */
		GetOuterAPSWeapon()->isBoltForward = true;
	}

	/* Return back to normal active state */
	GetOuterAPSWeapon()->goToState(GetOuterAPSWeapon()->weaponStates.activeState);

}

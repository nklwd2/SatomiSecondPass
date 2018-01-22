// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "HitscanFiringComponent.h"

UHitscanFiringComponent::UHitscanFiringComponent(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{


}

FHitResult UHitscanFiringComponent::fire(void) {
	

	/*
	//
	const int32 randomSeed = FMath::Rand();
	FRandomStream weaponRandomStream(randomSeed);
	const float currentSpread = GetCurrentSpread();
	const float coneHalfAngle = FMath::DegreesToRadians(currentSpread * 0.5f);

	const FVector aimDir = GetAdjustAim();
	const FVector startTrace = GetCameraDamageStartLocation(AimDir);
	const FVector shootDir = weaponRandomStream.VRandCone(AimDir, coneHalfAngle, coneHalfAngle);
	const FVector endTrace = startTrace + shootDir + InstantConfig.WeaponRange;

	const FHitResult impact = WeaponTrace(startTrace, endTrace);
	ProcesssInstantHit(impact, startTrace, shootDir, randomSeed, currentSpread);

	currentFiringSpread = FMath::Min(InstantConfig.FiringSpreadMax, currentFiringSpread, InstantConfig.FiringSpreadIncrement);
	*/

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PEW"));
		//UFiringComponent::WeaponTrace();
	}

	return FHitResult();
}


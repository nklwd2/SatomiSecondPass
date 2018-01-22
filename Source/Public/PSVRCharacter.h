// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PSCharacter.h"
#include "PSVRCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSATOMI_API APSVRCharacter : public APSCharacter
{
	GENERATED_UCLASS_BODY()

	void initializePlayerHands(const FObjectInitializer& ObjectInitializer);
	
	UPROPERTY(EditAnywhere, Category = "Components")
	class UMotionControllerComponent* VROriginComponent;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USkeletalMeshComponent* debugMirrorMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UMotionControllerComponent* leftHandController;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UMotionControllerComponent* rightHandController;
	
	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* leftHandGrabSphere;

	UPROPERTY(EditAnywhere, Category = "Components")
	class USphereComponent* rightHandGrabSphere;

	TOptional<APSEquippableActor*> pickupEquippableActorIfAble(const EHandSpecifier& hand) override;

	TOptional<APSEquippableActor*> simplisticCanPickupImplementation(const EHandSpecifier& hand) const;
	
};

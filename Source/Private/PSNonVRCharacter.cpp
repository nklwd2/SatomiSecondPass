// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSNonVRCharacter.h"

APSNonVRCharacter::APSNonVRCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UPSCharacterMovementComponent>(APSCharacter::CharacterMovementComponentName)) {

	initializePlayerHands();

	/* Player Camera */
	firstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	firstPersonCameraComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	firstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	firstPersonCameraComponent->bUsePawnControlRotation = true;
	IsFirstPersonPerspective = true;
}



void APSNonVRCharacter::initializePlayerHands() {

	/* This method should always be overridden */

	/* Attach Left Hand First person model to Player Camera */
	leftHandMesh->SetupAttachment(firstPersonCameraComponent);

	/* Attach Right Hand First Person Model to Player Camera*/
	rightHandMesh->SetupAttachment(firstPersonCameraComponent);
}
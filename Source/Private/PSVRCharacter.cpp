// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "MotionControllerComponent.h"
#include "PSBodyTypes.h"
#include "PSVRCharacter.h"

APSVRCharacter::APSVRCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UPSCharacterMovementComponent>(APSCharacter::CharacterMovementComponentName)) {

	initializePlayerHands(ObjectInitializer);
}

void APSVRCharacter::initializePlayerHands(const FObjectInitializer& ObjectInitializer) {

	/* This method should always be overridden */

	/* Create VR Scene Root */
	VROriginComponent = ObjectInitializer.CreateDefaultSubobject<UMotionControllerComponent>(this, TEXT("VROrigin"));
	VROriginComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	/* Debug VR Mesh */
	debugMirrorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("MirrorMesh"));
	debugMirrorMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	/* Player Camera */
	firstPersonCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	firstPersonCameraComponent->AttachToComponent(VROriginComponent, FAttachmentTransformRules::KeepRelativeTransform);
	IsFirstPersonPerspective = true;


	/* Left Motion Controller Initialization */
	leftHandController = ObjectInitializer.CreateDefaultSubobject<UMotionControllerComponent>(this, TEXT("LeftHandController"));
	leftHandController->Hand = EControllerHand::Left;
	leftHandController->bDisableLowLatencyUpdate = true;
	leftHandController->SetupAttachment(VROriginComponent);

	/* Right Motion Controller Initialization */
	rightHandController = ObjectInitializer.CreateDefaultSubobject<UMotionControllerComponent>(this, TEXT("RightHandController"));
	rightHandController->Hand = EControllerHand::Right;
	rightHandController->bDisableLowLatencyUpdate = true;
	rightHandController->SetupAttachment(VROriginComponent);

	leftHandGrabSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("LeftHandGrabSphere"));
	leftHandGrabSphere->AttachToComponent(leftHandController, FAttachmentTransformRules::KeepRelativeTransform);

	rightHandGrabSphere = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("RightHandGrabSphere"));
	rightHandGrabSphere->AttachToComponent(rightHandController, FAttachmentTransformRules::KeepRelativeTransform);

	/* Attach Left Hand Mesh to Left Motion Controller */
	leftHandMesh->AttachToComponent(leftHandController, FAttachmentTransformRules::KeepRelativeTransform);

	/* Attach Right Hand Mesh to Right Motion Controller */
	rightHandMesh->AttachToComponent(rightHandController, FAttachmentTransformRules::KeepRelativeTransform);
}

TOptional<APSEquippableActor*> APSVRCharacter::pickupEquippableActorIfAble(const EHandSpecifier& hand) {


	//TODO Check Hand Animation State Machine to see if it's in potential pickup animation state, if so pickup current focus
	/*if(isHandAnimationControllerInCanPickupState()) {

	}*/

	return simplisticCanPickupImplementation(hand);
}

TOptional<APSEquippableActor*> APSVRCharacter::simplisticCanPickupImplementation(const EHandSpecifier& hand) const {
	
	auto&& optionalEquippableActor = TOptional<APSEquippableActor*>();

	TArray<AActor*> overlappingActors;
	auto worldLocation = FVector::ZeroVector;

	class TSubclassOf<APSEquippableActor> test = TSubclassOf<APSEquippableActor>();
	if (hand == EHandSpecifier::LEFT_HAND) {

		leftHandGrabSphere->GetOverlappingActors(overlappingActors, test);
		worldLocation = leftHandGrabSphere->GetComponentLocation();
	}
	else if (hand == EHandSpecifier::RIGHT_HAND) {
		rightHandGrabSphere->GetOverlappingActors(overlappingActors, test);
		worldLocation = rightHandGrabSphere->GetComponentLocation();
	}

	APSEquippableActor* nearestActor = nullptr;
	float nearestOverlap = 0.0f;

	for (auto overlappedActor : overlappingActors) {
		float currentOverlap = (overlappedActor->GetActorLocation() - worldLocation).Size();

		if (currentOverlap > nearestOverlap) {
			nearestOverlap = currentOverlap;
			nearestActor = Cast<APSEquippableActor>(overlappedActor);
		}
	}

	if (nearestActor != nullptr) {
		optionalEquippableActor = nearestActor;
	}

	return optionalEquippableActor;
}

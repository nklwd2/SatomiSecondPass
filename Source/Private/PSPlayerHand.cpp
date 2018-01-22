// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSEquippableActor.h"
#include "PSPlayerHand.h"

APSPlayerHand::APSPlayerHand(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer){

	handMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("TestHandMesh"));

	setHandToEmpty();

}

void APSPlayerHand::tryEquipHand(APSEquippableActor* itemToBeHeld)
{
	if (isHandEmpty()) {
		setCurrentlyHeldItem(itemToBeHeld);
		attachEquippableActorToHand(itemToBeHeld);
		//Any other state that needs to be changed in either the hand or AEquippleActor
	}else{
		//Something is already in hand, cannot equip another thing!
	}
}


void APSPlayerHand::TryUnequipHand()
{
	if (isHandEmpty()) {
		//Nothing in hand to unequip
	}else{
		setHandToEmpty();
		detachEquippableFromHand();
		//Any other state that needs to be changed in either hand or AEquippableActor
	}
}

void APSPlayerHand::attachEquippableActorToHand(APSEquippableActor* itemToBeHeld) const {
	verifySlow(itemToBeHeld != nullptr);
	verifySlow(itemToBeHeld->getEquippableActorMesh() != nullptr);

	itemToBeHeld->getEquippableActorMesh()->AttachToComponent(handMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, handGripSocketName);
}

void APSPlayerHand::detachEquippableFromHand() const {

	verifySlow(currentlyHeldItem != nullptr);
	verifySlow(currentlyHeldItem->getEquippableActorMesh() != nullptr);

	currentlyHeldItem->getEquippableActorMesh()->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
}

bool APSPlayerHand::isHandEmpty() const {
	return currentlyHeldItem == nullptr ? true : false;
}

void APSPlayerHand::setHandToEmpty() {
	
	currentlyHeldItem = nullptr;
}

void APSPlayerHand::setCurrentlyHeldItem(APSEquippableActor* itemTobeHeld) {
	
	currentlyHeldItem = itemTobeHeld;
}


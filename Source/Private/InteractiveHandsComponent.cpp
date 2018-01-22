// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSPlayerHand.h"
#include "InteractiveHandsComponent.h"
#include "PSWeapon.h"

// Sets default values for this component's properties
UInteractiveHandsComponent::UInteractiveHandsComponent(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	// ...

	//leftHandMotionControllerComponent = ObjectInitializer.CreateDefaultSubobject<UMotionControllerComponent>(this, TEXT("LeftHandMotionControllerComponent"));
	//rightHandMotionControllerComponent = ObjectInitializer.CreateDefaultSubobject<UMotionControllerComponent>(this, TEXT("RightHandMotionControllerComponent"));

	leftHandMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("LeftHandMesh"));
	rightHandMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("RightHandMesh"));



	leftHandcurrentlyHeldItem = nullptr;
	rightHandcurrentlyHeldItem = nullptr;
}

// Called when the game starts
void UInteractiveHandsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UInteractiveHandsComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UInteractiveHandsComponent::tryEquipHand(const EHandSpecifier& hand, APSEquippableActor* itemToBeEquipped)
{
	if (isHandEmpty(hand)) {
		setCurrentlyHeldItem(hand, itemToBeEquipped);
		attachEquippableActorToHand(hand, itemToBeEquipped);
	}
}

void UInteractiveHandsComponent::tryUnequipHand(const EHandSpecifier& hand)
{
	detachEquippableFromHand(hand);
}

void UInteractiveHandsComponent::tryUseLeftHand() const {

	useItemOrClenchFist(leftHandcurrentlyHeldItem);
}

void UInteractiveHandsComponent::tryUseRightHand() const {
	
	useItemOrClenchFist(rightHandcurrentlyHeldItem);
}

void UInteractiveHandsComponent::useItemOrClenchFist(APSEquippableActor* heldItem) {
	if (heldItem == nullptr) {
		//Do empty hands stuff, like clenching fist
		//TODO implement clenching fist
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Nothing to use in hand!"));
		}
	}
	else {
		heldItem->use();
	}
}

void UInteractiveHandsComponent::tryReloadLeftHand() const {

	reloadItemOrDisplayWarning(leftHandcurrentlyHeldItem);
}

void UInteractiveHandsComponent::tryReloadRightHand() const {
	
	reloadItemOrDisplayWarning(rightHandcurrentlyHeldItem);
}

void UInteractiveHandsComponent::reloadItemOrDisplayWarning(APSEquippableActor* heldItem) const {
	
	if(heldItem == nullptr || !heldItem->IsA(APSWeapon::StaticClass())) {
		//Held item can't be reloaded, do nothing
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Nothing to reload in right hand!"));
		}
	}
	else {
		Cast<APSWeapon>(heldItem)->reload();
	}
}

void UInteractiveHandsComponent::attachEquippableActorToHand(const EHandSpecifier& hand, APSEquippableActor* itemToBeHeld) const {
	
	verifySlow(itemToBeHeld != nullptr);
	verifySlow(itemToBeHeld->getEquippableActorMesh() != nullptr);

	if(hand == EHandSpecifier::LEFT_HAND) {
		verifySlow(leftHandMesh != nullptr);
		itemToBeHeld->getEquippableActorMesh()->AttachToComponent(leftHandMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, handGripSocketName);
	}else {
		verifySlow(rightHandMesh != nullptr);
		itemToBeHeld->getEquippableActorMesh()->AttachToComponent(rightHandMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, handGripSocketName);
	}
	
}

void UInteractiveHandsComponent::detachEquippableFromHand(const EHandSpecifier& hand) const {
	
	if (hand == EHandSpecifier::LEFT_HAND) {

		verifySlow(leftHandcurrentlyHeldItem != nullptr);
		verifySlow(leftHandcurrentlyHeldItem->getEquippableActorMesh() != nullptr);

		leftHandcurrentlyHeldItem->getEquippableActorMesh()->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	}else {
		verifySlow(rightHandcurrentlyHeldItem != nullptr);
		verifySlow(rightHandcurrentlyHeldItem->getEquippableActorMesh() != nullptr);

		rightHandcurrentlyHeldItem->getEquippableActorMesh()->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	}
}

bool UInteractiveHandsComponent::isHandEmpty(const EHandSpecifier& hand) const {
	if(hand == EHandSpecifier::LEFT_HAND) {
		return leftHandcurrentlyHeldItem == nullptr ? true : false;
	}else {
		return rightHandcurrentlyHeldItem == nullptr ? true : false;
	}
}

void UInteractiveHandsComponent::setHandToEmpty(const EHandSpecifier& hand) {
	
	if(hand == EHandSpecifier::LEFT_HAND) {
		leftHandcurrentlyHeldItem = nullptr;
	}else {
		rightHandcurrentlyHeldItem = nullptr;
	}
}

void UInteractiveHandsComponent::setCurrentlyHeldItem(const EHandSpecifier& hand, APSEquippableActor* itemTobeHeld) {
	
	if (hand == EHandSpecifier::LEFT_HAND) {
		leftHandcurrentlyHeldItem = itemTobeHeld;
	}
	else {
		rightHandcurrentlyHeldItem = itemTobeHeld;
	}
}

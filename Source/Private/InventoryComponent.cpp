// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSEquippableActor.h"
#include "InventoryComponent.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize Hands
	//InventoryArray.Init(5);
	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


	AddDefaultItemsToInventory();
	// ...
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Inventory Initialized! " + FString::FromInt(InventoryArray.Num())));
	}
}

// Called every frame
void UInventoryComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UInventoryComponent::AddDefaultItemsToInventory(){


	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (const auto& inventorySlot : InventoryArray){

		const auto& newItem = GetWorld()->SpawnActor<APSEquippableActor>(inventorySlot.itemType, spawnInfo);
		Equip(inventorySlot.slotType, newItem);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Weapon Loop "));
		}
	}


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Inventory Weapons Initialized! "));
	}

}

APSEquippableActor* UInventoryComponent::GetEquippedItem(EInventorySlot::Type InventorySlot){

	return InventoryArray[InventorySlot].currentlyEquippedItem;
	
}

bool UInventoryComponent::Equip(EInventorySlot::Type InventorySlot, APSEquippableActor* InventoryObject){

	if (IsInventorySlotFilled(InventorySlot) != true){
		InventoryArray[InventorySlot].currentlyEquippedItem = InventoryObject;
		InventoryArray[InventorySlot].currentlyEquippedItem->getEquippableActorMesh()->AttachToComponent(skeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, InventoryArray[InventorySlot].slotEquipSocketName);//EAttachLocation::Type AttachType, bool bWeldSimulatedBodies
		return true;
	}
	else{
		return false;
	}
}

bool UInventoryComponent::Unequip(EInventorySlot::Type InventorySlot){

	if (InventoryArray[InventorySlot].currentlyEquippedItem != nullptr){

		//Do unequip Logic

		InventoryArray[InventorySlot].currentlyEquippedItem->DetachAllSceneComponents(skeletalMesh, FDetachmentTransformRules::KeepWorldTransform);//bMaintainWorldTransform
		//logic for putting into player hands or the ground?


		InventoryArray[InventorySlot].currentlyEquippedItem = nullptr;
		return true;
	}
	else{

		//Do equip Logic
		return false;
	}
}

bool UInventoryComponent::SwapInventorySlots(EInventorySlot::Type InventorySlot1, EInventorySlot::Type InventorySlot2){

	//unequip slot1
	InventoryArray[InventorySlot1].currentlyEquippedItem->DetachAllSceneComponents(skeletalMesh, FDetachmentTransformRules::KeepWorldTransform);
	//unequip slot2
	InventoryArray[InventorySlot2].currentlyEquippedItem->DetachAllSceneComponents(skeletalMesh, FDetachmentTransformRules::KeepWorldTransform);
	//Swap places in inventory
	InventoryArray.Swap(InventorySlot1, InventorySlot2);
	//equip slot1
	InventoryArray[InventorySlot1].currentlyEquippedItem->getEquippableActorMesh()->AttachToComponent(skeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, InventoryArray[InventorySlot1].slotEquipSocketName);//EAttachLocation::Type AttachType, bool bWeldSimulatedBodies
	//equip slot2
	InventoryArray[InventorySlot2].currentlyEquippedItem->getEquippableActorMesh()->AttachToComponent(skeletalMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, InventoryArray[InventorySlot2].slotEquipSocketName);//EAttachLocation::Type AttachType, bool bWeldSimulatedBodies

	verifySlow(this != nullptr);
	return true;
}

bool UInventoryComponent::IsInventorySlotFilled(EInventorySlot::Type InventorySlot){

	return InventoryArray[InventorySlot].currentlyEquippedItem != nullptr ? true : false;
}

bool UInventoryComponent::IsInventorySlotFilledWithUseableActor(EInventorySlot::Type InventorySlot){

	if (IsInventorySlotFilled(InventorySlot)/*&&  Actor in Inventory is type AUseableActor */ ){
		return true;
	}
	else{
		return false;
	}

}
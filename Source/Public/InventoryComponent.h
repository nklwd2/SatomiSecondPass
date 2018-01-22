// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"

#include "PSPlayerHand.h"
#include "InventoryComponent.generated.h"

UENUM()
namespace EInventorySlot
{

	enum Type
	{
		LEFT_HAND = 0,
		RIGHT_HAND = 1,
		LEFT_BACK = 2,
		RIGHT_BACK = 3,
		LEFT_THIGH = 4,
		RIGHT_THIGH = 5,
		UPPER_CHEST = 6,
		LOWER_CHEST = 7,
		HEAD = 8
	};

}

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config)
	FName slotEquipSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config)
	TEnumAsByte<EInventorySlot::Type> slotType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config)
	TSubclassOf<APSEquippableActor> itemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config)
	APSEquippableActor*  currentlyEquippedItem;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSATOMI_API UInventoryComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config)
	TArray<FInventorySlot> InventoryArray;

	/* Cached Skeletal Mesh Reference*/
	USkeletalMeshComponent* skeletalMesh;

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AddDefaultItemsToInventory(void);

	APSEquippableActor* GetEquippedItem(EInventorySlot::Type InventorySlot);

	virtual bool Equip(EInventorySlot::Type InventorySlot, APSEquippableActor* InventoryObject);

	virtual bool Unequip(EInventorySlot::Type InventorySlot);

	//virtual bool TransferEquipedInventoryToEmptySlot( EInventorySlot::Type, EInventorySlot::Type);

	virtual bool SwapInventorySlots(EInventorySlot::Type InventorySlot1, EInventorySlot::Type InventorySlot2);
	
	bool IsInventorySlotFilled(EInventorySlot::Type InventorySlot);

	bool IsInventorySlotFilledWithUseableActor(EInventorySlot::Type InventorySlot1);


};

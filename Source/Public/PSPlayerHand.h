// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PSBodyTypes.h"
#include "PSPlayerHand.generated.h"

class APSEquippableActor;
/**
 * 
 */
UCLASS()
class PROJECTSATOMI_API APSPlayerHand : public AActor
{
	GENERATED_UCLASS_BODY()

	//MotionController

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	class USkeletalMeshComponent* handMesh;

	const FName handGripSocketName = FName(TEXT("palmGrip"));

	void tryEquipHand(APSEquippableActor* itemToBeHeld);

	void TryUnequipHand();

	void attachEquippableActorToHand(APSEquippableActor* itemToBeHeld) const;

	void detachEquippableFromHand() const;

	bool isHandEmpty() const;

	void setHandToEmpty();

	void setCurrentlyHeldItem(APSEquippableActor* itemTobeHeld);

	FORCEINLINE APSEquippableActor* getHeldItem() const { return currentlyHeldItem; };

private:

	UPROPERTY()
	class APSEquippableActor* currentlyHeldItem;

	UPROPERTY()
	EHandSpecifier handSpecifier;

	UPROPERTY()
	bool IsUsingStandaloneHandMesh;

	//UPROPERTY()
	class UMotionControllerComponent* VRMotionController;
};

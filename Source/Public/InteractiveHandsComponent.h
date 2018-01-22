// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "InteractiveHandsComponent.generated.h"

class APSPlayerHand;
class UMotionControllerComponent;
class APSEquippableActor;
enum class EHandSpecifier : uint8;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSATOMI_API UInteractiveHandsComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

private:

	static void useItemOrClenchFist(APSEquippableActor* heldItem);

public:	

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	class APSPlayerHand* leftHand;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	class APSPlayerHand* rightHand;*/

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */

	class UMotionControllerComponent* leftHandMotionControllerComponent;

	class UMotionControllerComponent* rightHandMotionControllerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	class USkeletalMeshComponent* leftHandMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	class USkeletalMeshComponent* rightHandMesh;

	UPROPERTY()
	class APSEquippableActor* leftHandcurrentlyHeldItem;

	UPROPERTY()
	class APSEquippableActor* rightHandcurrentlyHeldItem;

	// Sets default values for this component's properties
	UInteractiveHandsComponent();

	// Called when the game starts
	void BeginPlay() override;
	
	// Called every frame
	void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	
	void tryEquipHand(const EHandSpecifier& hand, APSEquippableActor* itemToBeEquipped);

	void tryUnequipHand(const EHandSpecifier& hand);

	void tryUseRightHand() const;

	void tryUseLeftHand() const;

	void tryReloadRightHand() const;

	void tryReloadLeftHand() const;

	void reloadItemOrDisplayWarning(APSEquippableActor* heldItem) const;

	void attachEquippableActorToHand(const EHandSpecifier& hand, APSEquippableActor* itemToBeHeld) const;

	void detachEquippableFromHand(const EHandSpecifier& hand) const;

	bool isHandEmpty(const EHandSpecifier& hand) const;

	void setHandToEmpty(const EHandSpecifier& hand);

	void setCurrentlyHeldItem(const EHandSpecifier& hand, APSEquippableActor* itemTobeHeld);

	const FName handGripSocketName = FName(TEXT("palmGrip"));
};

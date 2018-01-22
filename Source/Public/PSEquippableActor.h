// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UseableActor.h"
#include "PSEquippableActor.generated.h"

class AUseableActor;
class APSCharacter;
enum class EHandSpecifier : uint8;

UENUM()
enum class EInventorySlotType : uint8
{
	TINY = 0, //Can be stored in Upper & lower front slots (Like grenades)
	SMALL = 1, //Can be stored in Leg slots (pistols)
	MEDIUM = 2, // Can be stored on Back Slots (Rilfes)
	LARGE = 3 // Can't be stored anywhere on person (Mini-gun)
};

UCLASS()
class PROJECTSATOMI_API APSEquippableActor : public AUseableActor
{
	GENERATED_UCLASS_BODY()

private:

	//Weapon's Mesh Model
	UPROPERTY(VisibleAnywhere, Category = Config)
	class USkeletalMeshComponent *equippableActorMesh;

	/* VR Grippable Spline, determines where a VR Hand will Grip*/
	UPROPERTY(VisibleAnywhere, Category = Config)
	class USplineComponent *VRsplineGripComponent;

	UPROPERTY()
	class APSCharacter* equippableActorOwner;

	EHandSpecifier bodyPartEquippedTo;
	
public:	

	// Sets default values for this actor's properties
	APSEquippableActor();


	UPROPERTY(VisibleAnywhere, Category = Config)
	class UPickupComponent* pickupComponent;

	FORCEINLINE USkeletalMeshComponent* getEquippableActorMesh() const {
		return equippableActorMesh;
	}

	FORCEINLINE APSCharacter* getOwnerPawn() const {
		return equippableActorOwner;
	}

	FORCEINLINE EHandSpecifier getEquippedBodyPart() const {
		return bodyPartEquippedTo;
	}

	void setEquippableActorMesh(USkeletalMeshComponent* actorMesh) {
		equippableActorMesh = actorMesh;
	}

	// Called when the game starts or when spawned
	void BeginPlay() override;
	
	// Called every frame
	void Tick( float DeltaSeconds ) override;

	virtual void equip(APSCharacter* newOwner, const EHandSpecifier &bodyPartToEquipTo);

	virtual void unequip();

};

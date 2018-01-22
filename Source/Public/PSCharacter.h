// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "PSCharacter.generated.h"

class UHealthComponent;
class APSEquippableActor;
class UInventoryComponent;
enum class EHandSpecifier : uint8;

USTRUCT(BlueprintType)
struct FCharacterConfig
{
	GENERATED_USTRUCT_BODY()

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config)
	float baseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Config)
	float baseLookUpRate;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	bool isUsingVR;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathNotificationDelegate);

UCLASS()
class PROJECTSATOMI_API APSCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** Cached PSCharacterMovement  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	class UPSCharacterMovementComponent* playerMovementComponent;

	// First Person Point of View Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	class UCameraComponent* firstPersonCameraComponent;

	// First Person Point of View Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	class USpringArmComponent* springArmComponent;

	//Inventory and Hands
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	class UInventoryComponent* inventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Config)
	class UHealthComponent* healthComponent;

	UPROPERTY()
	class UPickupCollectorComponent* pickupCollectorComponent;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* leftHandMesh;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* rightHandMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class APSEquippableActor* leftHandCurrentlyHeldItem;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class APSEquippableActor* rightHandCurrentlyHeldItem;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class TSubclassOf<APSEquippableActor> defaultLeftHandItem;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class TSubclassOf<APSEquippableActor> defaultRightHandItem;


	UPROPERTY(BlueprintAssignable, Category = "Test")
	FDeathNotificationDelegate onCharacterDeathNotifier;

public:

	UPROPERTY(EditAnywhere, Category = Config)
	FCharacterConfig charConfig;

	bool IsFirstPersonPerspective;


	// Sets default values for this character's properties
	void InitializeCharacterUsingConfig(FCharacterConfig characterConfig);

	void initializePlayerHandMeshes(const FObjectInitializer& objectInitializer);

	void InitializeRequiredDefaultCharacterComponents(const FObjectInitializer& objectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float deltaSeconds ) override;

	UFUNCTION()
	void onCharacterDeath();

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void MoveForward(const float value);
	virtual void MoveRight(const float value);

	void TurnAtRate(const float rate);
	void LookUpAtRate(const float rate);

	virtual void Jump();

	void tryEquipHand(const EHandSpecifier& hand, APSEquippableActor* itemToBeEquipped);
	bool tryUnequipHand(const EHandSpecifier& hand);
	void attachEquippableActorToHand(const EHandSpecifier& hand, APSEquippableActor* itemToBeHeld) const;
	void detachEquippableFromHand(const EHandSpecifier& hand) const;

	UStaticMeshComponent* getHandMesh(const EHandSpecifier &hand) const;

	/*Weapons and Inventory*/
	void tryActvateRightHandItem();
	void tryActivateLeftHandItem();
	bool isHandAnimationControllerInCanPickupState();
	virtual TOptional<APSEquippableActor*> pickupEquippableActorIfAble(const EHandSpecifier& hand);
	void useItemOrClenchFist(const EHandSpecifier& hand, APSEquippableActor* heldItem);

	void tryReloadRightHand() const;
	void tryReloadLeftHand() const;

	void reloadItemOrDisplayWarning(APSEquippableActor* heldItem) const;

	bool isHandEmpty(const EHandSpecifier& hand) const;

	void setHandToEmpty(const EHandSpecifier& hand);

	void setCurrentlyHeldItem(const EHandSpecifier& hand, APSEquippableActor* itemTobeHeld);

	const FName leftHandGripSocketName = FName(TEXT("LeftHandSocket"));
	const FName rightHandGripSocketName = FName(TEXT("RightHandSocket"));

	void AddDefaultItemsToHands();
	void AddItemToInventory(APSEquippableActor* item);
	void DropItemInWorld();

	void SwapItemInInventoryWithCurrentRightHand();
	void SwapItemInInventoryWithCurrentLeftHand();


	void ToggleCamera();

	float TakeDamage( float DamageAmount, struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;
public:

	//FORCEINLINE class USkeletalMeshComponent* GetFPSMesh() const { return firstPersonMesh;  }

	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return firstPersonCameraComponent; }
	
};

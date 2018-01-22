// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PSEquippableActor.h"
#include "PSWeapon.generated.h"

class UFiringComponent;
class UAmmoClipSystemComponent;
class UDamageCalculatorAndNotifier;
class UPSWeaponState;
enum class EInventorySlotType : uint8;

UENUM()
enum class EWeaponType : uint8
{
	HAND = 0,
	PISTOL = 1,
	SMG = 2,
	ASSAULT_RIFLE = 3,
	SNIPER_RIFLE = 4,
	SHOTGUN = 5,
	KNIFE = 6
};

UENUM()
enum class EWeaponFiringType : uint8
{
	HITSCAN = 0,
	PROJECTILE = 1,
	MELEE = 3
};

UENUM()
enum class EWeaponFiringMode : uint8
{
	SINGLE_SHOT = 0,
	TRIPLE_SHOT = 1,
	AUTOMATIC = 3,
	SPREADSHOT = 4
};

UENUM()
enum class EAmmoSystemType : uint8
{
	AMMO_CLIPS_AND_POOL = 0,
	AMMO_CLIPS_ONLY = 1,
	DURABILITY = 2,
	AMMO_POOL_ONLY = 3
};

UENUM()
enum class EWeaponChamberState {
	EMTPY,
	ROUND_CHAMBERED,
	SPENT_ROUND_CHAMBERED
};

USTRUCT()
struct FWeaponFiringMode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Config)
	EWeaponFiringType firingType;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	EWeaponFiringMode firingMode;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float baseTimeBetweenShots;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	UParticleSystem* weaponBulletPathFx;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	UParticleSystem* weaponMuzzleFx;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	UParticleSystem* weaponprojectileParticleEffect;

	/** force feedback effect to play when the weapon is fired */
	UPROPERTY(EditDefaultsOnly, Category = Config)
	UForceFeedbackEffect* FireForceFeedback;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	USoundBase* firstPersonFireSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	USoundBase* thirdPersonFireSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	USoundBase* ReloadSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	USoundBase* FireLoopingSound;

};

USTRUCT()
struct FWeaponDamage
{
	GENERATED_USTRUCT_BODY()
};

USTRUCT()
struct FWeaponAccuracy
{
	GENERATED_USTRUCT_BODY()

};

USTRUCT()
struct FWeaponAmmo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = Config)
	EAmmoSystemType ammoSystemType;

};

USTRUCT()
struct FWeaponMiscStats
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Config)
	EInventorySlotType weaponSlotType;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FName muzzleBoneName;
};

USTRUCT()
struct FWeaponAnim
{
	GENERATED_USTRUCT_BODY()

	/** animation played on pawn (1st person view) */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* playerHandAnimation;

	/** animation played on pawn (3rd person view) */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* weaponFiringAnimation;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* weaponReloadingAnimation;
};

USTRUCT()
struct FWeaponSounds
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Config)
	USoundBase* lowAmmoSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	USoundBase* bringUpSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	USoundBase* putDownSound;

};

USTRUCT(BlueprintType)
struct FWeaponConfig
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Config)
	EWeaponType weaponType;


	UPROPERTY(EditDefaultsOnly, Category = Config)
	TArray<FWeaponFiringMode> firingModes;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponDamage weaponDamage;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponAccuracy weaponAccuracy;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponAmmo weaponAmmo;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponMiscStats weaponMiscStats;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponAnim weaponAnimations;

	UPROPERTY(EditAnywhere, Category = Config)
	bool bIsMelee;
};

USTRUCT()
struct FWeaponStates{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class UPSWeaponState* currentState;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class UPSWeaponState* activeState;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class UPSWeaponState* firingState;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class UPSWeaponState* cockingState;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class UPSWeaponState* feedingState;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class UPSWeaponState* inactiveState;

};

UCLASS(Blueprintable)
class PROJECTSATOMI_API APSWeapon : public APSEquippableActor
{
	GENERATED_UCLASS_BODY()

	friend class UPSWeaponState;
	friend class UPSWeaponActiveState;

	UPROPERTY(Transient)
	class APSCharacter* myPawn;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponConfig weaponConfig;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FWeaponStates weaponStates;

	bool isHammerEngaged;
	EWeaponChamberState weaponChamberState;
	bool isRoundInMagazine;
	bool isBoltForward;

	uint8 currentFireModeNum;


	//Weapon's AmmoComponent
	UPROPERTY(EditDefaultsOnly, Category = Config)
	class UAmmoClipSystemComponent* ammoSystemComponent;

	// Weapon's ballistic firing component
	UPROPERTY(EditDefaultsOnly, Category = Config)
	class TSubclassOf<UFiringComponent> firingComponentType;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class UFiringComponent* firingSystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class UDamageCalculatorAndNotifier* damageCalculatorComponent;

	//Weapon's Sound Player
	UAudioComponent *audioComponent;

	//Weapon's Particle Emitter
	UParticleSystemComponent *particleComponent;

	//Weapon's State
	//TSubclassOf<UPSWeaponState> weaponState;

	
public:	
	// Sets default values for this actor's properties
	APSWeapon();

	// Called when the game starts or when spawned
	void BeginPlay() override;
	
	// Called every frame
	void Tick( float DeltaSeconds ) override;

	virtual void goToState(class UPSWeaponState* newState);

	//Activate AWeapon
/*	void virtual ActivateWeapon(void);

	//Deactivate AWeapon
	void virtual DeactivateWeapon(void);
	
	//Check to see if AWeapon can be Activated
	virtual bool CanActivate(void);*/

	/* Set the Weapon's Owner */
	void SetOwningPawn(APSCharacter* NewOwner);

	/* Weapon use and Activation*/
	void use() override;

	void pullTrigger();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void fire();

	virtual void dryFire();

	virtual float getTimeBetweenShots(const uint8 fireModeNum);

	void playHandAnimation(UAnimMontage* handAnimation) const;

	void playWeaponAnimation(UAnimMontage* weaponAnimation) const;

	void playWeaponSound(USoundBase* weaponSoundToPlay);

	void spawnWeaponParticleSystem(UParticleSystem* particleSystemToSpawn, FName skeletalMeshSocketToSpawnFrom);

	void spawnImpactEffects(const FVector& targetLocation, uint8 fireMode, const FVector* spawnLocation, const FRotator& spawnRotation);

	/* Ammo Related*/
	void reload();
	
	FVector getWeaponMuzzleVector() const;

	/*UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void StartFire(uint8 FireModeNum);
	UFUNCTION(BlueprintCallable, Category = Weapon)
	virtual void StopFire(uint8 FireModeNum);*/

	/** Tell server fire button was pressed.  bClientFired is true if client actually fired weapon. */
	//UFUNCTION(Server, unreliable, WithValidation)
	//virtual void ServerStartFire(uint8 FireModeNum, uint8 FireEventIndex, bool bClientFired);

	/** ServerStartFire, also pass Z offset since it is interpolating. */
	//UFUNCTION(Server, unreliable, WithValidation)
	//virtual void ServerStartFireOffset(uint8 FireModeNum, uint8 FireEventIndex, uint8 ZOffset, bool bClientFired);

	/** Just replicated ZOffset for shot fire location. */
	//UPROPERTY()
	//float FireZOffset;

	/** When received FireZOffset - only valid for same time and next frame. */
	//UPROPERTY()
	//float FireZOffsetTime;

	//UFUNCTION(Server, Reliable, WithValidation)
	//	virtual void ServerStopFire(uint8 FireModeNum, uint8 FireEventIndex);

	/** Used when client just triggered a fire on a held trigger right before releasing.*/
//	UFUNCTION(Server, Reliable, WithValidation)
//		virtual void ServerStopFireRecent(uint8 FireModeNum, uint8 FireEventIndex);

//	virtual bool BeginFiringSequence(uint8 FireModeNum, bool bClientFired);
	//virtual void EndFiringSequence(uint8 FireModeNum);

	/** Returns true if weapon will fire a shot this frame - used for network synchronization */
	//virtual bool WillSpawnShot(float DeltaTime);

	/** Returns true if weapon can fire again (fire button is pressed, weapon is held, has ammo, etc.). */
//	virtual bool CanFireAgain();

	/** hook when the firing state starts; called on both client and server */
//	UFUNCTION(BlueprintNativeEvent)
//	void OnStartedFiring();

	/** hook for the return to active state (was firing, refire timer expired, trigger released and/or out of ammo)  */
	//UFUNCTION(BlueprintNativeEvent)
//	void OnStoppedFiring();

	/* Last time weapon fired because of held trigger*/
//	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	//float LastContinuedFiring;

	/** Return true and  trigger effects if should continue firing, otherwise sends weapon to its active state */
//	virtual bool HandleContinuedFiring();

	/** hook for when the weapon has fired, the refire delay passes, and the user still wants to fire (trigger still down) so the firing loop will repeat */
//	UFUNCTION(BlueprintNativeEvent)
	//void OnContinuedFiring();

	/** plays an anim on the weapon and optionally hands
	* automatically handles fire rate modifiers by default, overridden if RateOverride is > 0.0
	*/
	//UFUNCTION(BlueprintCallable, Category = "Weapon")
	//virtual void PlayWeaponAnim(UAnimMontage* WeaponAnim, UAnimMontage* HandsAnim = NULL, float RateOverride = 0.0f);
	/** returns montage to play on the weapon for the specified firing mode */
//	UFUNCTION(BlueprintCallable, Category = "Weapon")
//	virtual UAnimMontage* GetFiringAnim(uint8 FireMode, bool bOnHands = false) const;

	/* Weapon State */
//	virtual void StateChanged(){}

};

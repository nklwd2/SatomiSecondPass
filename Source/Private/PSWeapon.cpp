// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "AmmoClipSystemComponent.h"
#include "FiringComponent.h"
#include "PSCharacter.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "DamageCalculatorAndNotifier.h"
#include "PSWeaponActiveState.h"
#include "PSWeaponCockingState.h"
#include "PSWeaponFeedingState.h"
#include "PSWeaponFiringState.h"
#include "PSWeapon.h"
#include "PSGameplayStatics.h"
#include "PSFPSPlayerController.h"

// Sets default values
APSWeapon::APSWeapon(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ammoSystemComponent = ObjectInitializer.CreateDefaultSubobject<UAmmoClipSystemComponent>(this, TEXT("AmmoComponent"));
	firingSystemComponent = ObjectInitializer.CreateDefaultSubobject<UFiringComponent>(this, TEXT("FiringComponent"));
	damageCalculatorComponent = ObjectInitializer.CreateDefaultSubobject<UDamageCalculatorAndNotifier>(this, TEXT("DamageCalculatorAndNotifierComponent"));
	//firingComponentType = ObjectInitializer.CreateDefaultSubobject<UFiringComponent>(this, TEXT("FiringComponentType"));
	
	/*if (!firingComponentType) {
		firingComponentType = UFiringComponent::StaticClass();
	}*/

	//firingSystemComponent = Cast<UFiringComponent>(ObjectInitializer.CreateDefaultSubobject(this, TEXT("FiringComponent"), firingComponentType, firingComponentType, false, false, false));

	weaponStates.activeState = ObjectInitializer.CreateDefaultSubobject<UPSWeaponActiveState>(this, TEXT("ActiveState"));
	weaponStates.inactiveState = ObjectInitializer.CreateDefaultSubobject<UPSWeaponActiveState>(this, TEXT("InactiveState"));
	weaponStates.cockingState = ObjectInitializer.CreateDefaultSubobject<UPSWeaponCockingState>(this, TEXT("CockingState"));
	weaponStates.feedingState = ObjectInitializer.CreateDefaultSubobject<UPSWeaponFeedingState>(this, TEXT("FeedingState"));
	weaponStates.firingState = ObjectInitializer.CreateDefaultSubobject<UPSWeaponFiringState>(this, TEXT("FiringState"));

	weaponStates.currentState = weaponStates.activeState;

}

// Called when the game starts or when spawned
void APSWeapon::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Base Weapon Initialized!"));
	}

	isHammerEngaged = true;
	isBoltForward = true;
	isRoundInMagazine = false;
	weaponChamberState = EWeaponChamberState::ROUND_CHAMBERED;
	currentFireModeNum = 0;
}

// Called every frame
void APSWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	
}

void APSWeapon::SetOwningPawn(APSCharacter* newOwner){
	if (myPawn != newOwner)
	{
		Instigator = newOwner;
		myPawn = newOwner;
		// net owner for RPC calls
		SetOwner(newOwner);
	}
}

void APSWeapon::goToState(class UPSWeaponState* newState) {
	
	if (newState == nullptr) {
		verifySlow(newState != nullptr);
	} else if(weaponStates.currentState != newState){
		
		/* Set previous state to current*/

		auto prevState = weaponStates.currentState;

		/* End current state*/
		if (weaponStates.currentState != nullptr) {
			weaponStates.currentState->endState();
		}

		/* Check current state is still previous, if so change current state and Begin new State*/
		if (weaponStates.currentState == prevState) {
			weaponStates.currentState = newState;
			weaponStates.currentState->beginState(prevState);
		}

	}
}

void APSWeapon::use(){

	pullTrigger();
	
}

void APSWeapon::pullTrigger() {

	verifySlow(weaponStates.currentState != nullptr);

	if(weaponStates.currentState != nullptr){
		weaponStates.currentState->triggerPulled(currentFireModeNum);
	}
}

void APSWeapon::fire()
{
	/* Precondition sanity checks */
	verifySlow(isHammerEngaged == true);
	verifySlow(weaponChamberState == EWeaponChamberState::ROUND_CHAMBERED);
	verifySlow(isBoltForward == true);

	/* Hammer has been triggered and set off round*/
	isHammerEngaged = false;//TODO Possibly move back into weapon firing state

	/* Expel bullet from round */
	weaponChamberState = EWeaponChamberState::SPENT_ROUND_CHAMBERED;

	/* Fire raytrace */
	const auto&& hitResult = firingSystemComponent->fire();

	/* Bolt flies backward */
	isBoltForward = false;//TODO possibly move back into WeaponFiringState

	/* Play flashy gun firing effects */
	playWeaponAnimation(weaponConfig.weaponAnimations.weaponFiringAnimation);
	playHandAnimation(weaponConfig.weaponAnimations.playerHandAnimation);
	playWeaponSound(weaponConfig.firingModes[currentFireModeNum].firstPersonFireSound);
	spawnWeaponParticleSystem(weaponConfig.firingModes[currentFireModeNum].weaponMuzzleFx, FName(TEXT("Fire_FX_Slot")));
	//UPSGameplayStatics::spawnDebugTextAtLocation(FString(TEXT("Pew!")), FColor::Yellow, 12, 5, GetActorLocation() + FVector(0, 0, 20), GetWorld(), Cast<APSFPSPlayerController>(Cast<APSCharacter>(getOwnerPawn())->GetController()));
	//TODO relocate blueprint storage and finding in player controller constructor

	//spawnImpactEffect();
	/* Handle hit result damage */
	damageCalculatorComponent->calculateAndApplyDamageIfApplicable(MoveTemp(hitResult));
	
}

void APSWeapon::dryFire() {
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("*Click*"));
	}

	/* Hammer has been triggered and hit empty chamber*/
	isHammerEngaged = false;

	/* Play Dry Fire Sound */
}

float APSWeapon::getTimeBetweenShots(const uint8 fireModeNum){

	verifySlow(weaponConfig.firingModes[fireModeNum].baseTimeBetweenShots > 0.0f);
	return weaponConfig.firingModes[fireModeNum].baseTimeBetweenShots;
}

void APSWeapon::playHandAnimation(UAnimMontage* handAnimation) const {
	//TODO make seperate meshes for playig hand animation on denpnding on if it's VR or not
	getOwnerPawn()->getHandMesh(getEquippedBodyPart());

	/*if (handAnimation) {
		getOwnerPawn()->getHandMesh(getEquippedBodyPart())->GetAnimInstance()->Montage_Play(handAnimation, 1.0f);
	}*/
}

void APSWeapon::playWeaponAnimation(UAnimMontage* weaponAnimation) const {

	if (weaponAnimation && getEquippableActorMesh() && getEquippableActorMesh()->GetAnimInstance()){
		getEquippableActorMesh()->GetAnimInstance()->Montage_Play(weaponAnimation, 1.0f);
	}
}

void APSWeapon::playWeaponSound(USoundBase* weaponSoundToPlay) {
	
	UGameplayStatics::PlaySoundAtLocation(this, weaponSoundToPlay, GetActorLocation(), FRotator::ZeroRotator, 1.0f, 1.0f, 0.0, nullptr, nullptr);
}

void APSWeapon::spawnWeaponParticleSystem(UParticleSystem* particleSystemToSpawn, FName skeletalMeshSocketToSpawnFrom) {
	
	UGameplayStatics::SpawnEmitterAttached(particleSystemToSpawn, getEquippableActorMesh(), skeletalMeshSocketToSpawnFrom, FVector(ForceInit), FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true);
}

void APSWeapon::spawnImpactEffects(const FVector& targetLocation, uint8 fireMode, const FVector* spawnLocation, const FRotator& spawnRotation) {
	

}

void APSWeapon::reload(){

	verifySlow(ammoSystemComponent != nullptr);

	if (ammoSystemComponent->canReload()){

		//play animation and wait then reload
		ammoSystemComponent->reloadAmmoSystem();
		isHammerEngaged = true;//TODO this should be a state transition to cocking
		weaponChamberState = EWeaponChamberState::ROUND_CHAMBERED;
		playWeaponAnimation(weaponConfig.weaponAnimations.weaponReloadingAnimation);
	}
	else{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Can't reload!"));
	}
}

FVector APSWeapon::getWeaponMuzzleVector() const {
	
	return getEquippableActorMesh()->GetSocketLocation(FName(TEXT("Fire_FX_Slot")));
}

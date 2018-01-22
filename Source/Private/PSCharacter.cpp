// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSCharacterMovementComponent.h"
#include "PSEquippableActor.h"
#include "PSWeapon.h"
#include "InteractiveHandsComponent.h"
#include "HealthComponent.h"
#include "InventoryComponent.h"
#include "PSCharacter.h"

APSCharacter::APSCharacter(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer.SetDefaultSubobjectClass<UPSCharacterMovementComponent>(APSCharacter::CharacterMovementComponentName)){

	charConfig.baseTurnRate = 45.f;
	charConfig.baseLookUpRate = 45.f;
	charConfig.isUsingVR = false;
	leftHandCurrentlyHeldItem = nullptr;
	rightHandCurrentlyHeldItem = nullptr;

	InitializeRequiredDefaultCharacterComponents(MoveTemp(ObjectInitializer));
	initializePlayerHandMeshes(MoveTemp(ObjectInitializer));

	healthComponent->OnHealthDepleted.AddDynamic(this, &APSCharacter::onCharacterDeath);

}

void APSCharacter::InitializeCharacterUsingConfig(FCharacterConfig characterConfig){

	charConfig = characterConfig;
}

void APSCharacter::InitializeRequiredDefaultCharacterComponents(const FObjectInitializer& objectInitializer) {

	/* Set Default Player Collision Size*/
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	/* Make Player's Body Mesh - TEMPORARY UNTIL VR BODY MESH IMPLEMENTED */
	GetMesh()->SetOwnerNoSee(false);

	/* Camera Boom for Debug Third Person Character Model Viewing*/
	springArmComponent = objectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("SpringArmComponent"));
	springArmComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	springArmComponent->TargetArmLength = 300.0f;
	springArmComponent->bUsePawnControlRotation = true;

	/* Player Camera */
	/*firstPersonCameraComponent = objectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	firstPersonCameraComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	firstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
	firstPersonCameraComponent->bUsePawnControlRotation = true;
	IsFirstPersonPerspective = true;*/

	/* Player Pawn Movement */
	playerMovementComponent = Cast<UPSCharacterMovementComponent>(GetCharacterMovement());

	/* Player Inventory - DOES NOT INCLUDE HANDS */
	inventoryComponent = objectInitializer.CreateDefaultSubobject<UInventoryComponent>(this, TEXT("InventoryComponent"));

	/* Player Health */
	healthComponent = objectInitializer.CreateDefaultSubobject<UHealthComponent>(this, TEXT("HealthComponent"));

}

void APSCharacter::initializePlayerHandMeshes(const FObjectInitializer& objectInitializer) {
	
	/* Player's Left Hand Mesh */
	leftHandMesh = objectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("leftHand"));
	leftHandMesh->bOnlyOwnerSee = true;
	leftHandMesh->bOwnerNoSee = false;
	leftHandMesh->bCastDynamicShadow = false;
	leftHandMesh->bReceivesDecals = false;
	//leftHandMesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	leftHandMesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	leftHandMesh->SetCollisionObjectType(ECC_Pawn);
	leftHandMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	leftHandMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	/* Player's Right Hand Mesh */
	rightHandMesh = objectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("RightHand"));
	rightHandMesh->bOnlyOwnerSee = true;
	rightHandMesh->bOwnerNoSee = false;
	rightHandMesh->bCastDynamicShadow = false;
	rightHandMesh->bReceivesDecals = false;
	//rightHandMesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	rightHandMesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	rightHandMesh->SetCollisionObjectType(ECC_Pawn);
	rightHandMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	rightHandMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void APSCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("We are using PSCharacter!"));
	}

	//initializePlayerHands();

	AddDefaultItemsToHands();
}

// Called every frame
void APSCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APSCharacter::onCharacterDeath() {
	
	onCharacterDeathNotifier.Broadcast();
}

void APSCharacter::MoveForward(const float value){

	if (value != 0.0f)
	{
		UE_LOG(LogTemp, Log, TEXT("MoveForward"));
		//Find Forward Vector
		const auto rotation = GetControlRotation();
		const auto yawRotation = (playerMovementComponent) ? rotation : FRotator(0, rotation.Yaw, 0);

		//Tell the movementcomponent to go forward in said direction 
		AddMovementInput(FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X), value);
	}

}

void APSCharacter::AddDefaultItemsToHands(){

	FActorSpawnParameters spawnInfo;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (defaultLeftHandItem != nullptr) {
		tryEquipHand(EHandSpecifier::LEFT_HAND, GetWorld()->SpawnActor<APSEquippableActor>(defaultLeftHandItem, spawnInfo));
	}

	if(defaultRightHandItem != nullptr) {
		tryEquipHand(EHandSpecifier::RIGHT_HAND, GetWorld()->SpawnActor<APSEquippableActor>(defaultRightHandItem, spawnInfo));
	}

	/*for (const auto& inventorySlot : charConfig.inventory){

		if (inventorySlot.currentlyEquippedItem){
			FActorSpawnParameters spawnInfo;
			spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			const auto& newItem = GetWorld()->SpawnActor<AEquippableActor>(inventorySlot.currentlyEquippedItem, spawnInfo);
			AddItemToInventory(newItem);
		}
	}*/
		
}

void APSCharacter::AddItemToInventory(APSEquippableActor* item){

	if (item){
		// item->OnEnterInventory();
		//	inventoryComponent->equip(EInventorySlot::RIGHT_HAND, GetWorld()->SpawnActor<AEquippableActor>(DefaultInventoryToAdd[0]));
	}

}

void APSCharacter::DropItemInWorld(){

}


void APSCharacter::ToggleCamera()
{

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Camera Toggled!"));


	firstPersonCameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	
	if (IsFirstPersonPerspective && charConfig.isUsingVR == false) {
		firstPersonCameraComponent->AttachToComponent(springArmComponent, FAttachmentTransformRules::KeepRelativeTransform);
		firstPersonCameraComponent->RelativeLocation = FVector(0, 0, 0); // Position the camera
		IsFirstPersonPerspective = false;

		leftHandMesh->SetVisibility(false);
		rightHandMesh->SetVisibility(false);
		GetMesh()->SetOwnerNoSee(false);
	}
	else if(charConfig.isUsingVR == false){
		firstPersonCameraComponent->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		firstPersonCameraComponent->RelativeLocation = FVector(0, 0, 64.f); // Position the camera
		firstPersonCameraComponent->bUsePawnControlRotation = true;
		IsFirstPersonPerspective = true;

		leftHandMesh->SetVisibility(true);
		rightHandMesh->SetVisibility(true);

		GetMesh()->SetOwnerNoSee(true);
		
	}

}

float APSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) {

	return healthComponent->takeHealthDamage(DamageAmount);
}

void APSCharacter::MoveRight(const float value) {

	if (value != 0.0f)
	{
		// find out which way is right
		const auto rotation = GetControlRotation();
		const auto yawRotation = FRotator(0, rotation.Yaw, 0);

		// add movement in right direction
		AddMovementInput(FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y), value);
	}
}

void APSCharacter::TurnAtRate(const float rate){

	// calculate delta for this frame from the rate information
	AddControllerYawInput(rate * charConfig.baseTurnRate * GetWorld()->GetDeltaSeconds());

}

void APSCharacter::LookUpAtRate(const float rate){

	// calculate delta for this frame from the rate information
	AddControllerPitchInput(rate * charConfig.baseLookUpRate * GetWorld()->GetDeltaSeconds());

}

void APSCharacter::Jump(){

}


void APSCharacter::tryEquipHand(const EHandSpecifier& hand, APSEquippableActor* itemToBeEquipped) {
	if (isHandEmpty(hand)) {
		setCurrentlyHeldItem(hand, itemToBeEquipped);
		attachEquippableActorToHand(hand, itemToBeEquipped);
	}
}

bool APSCharacter::tryUnequipHand(const EHandSpecifier& hand) {

	if (!isHandEmpty(hand)) {
		detachEquippableFromHand(hand);
		setHandToEmpty(hand);
		return true;
	}

	return false;
}


void APSCharacter::attachEquippableActorToHand(const EHandSpecifier& hand, APSEquippableActor* itemToBeHeld) const {

	verifySlow(itemToBeHeld != nullptr);
	verifySlow(itemToBeHeld->getEquippableActorMesh() != nullptr);

	FAttachmentTransformRules rules = FAttachmentTransformRules::SnapToTargetIncludingScale;
	rules.bWeldSimulatedBodies = true;

	if (hand == EHandSpecifier::LEFT_HAND) {
		//verifySlow(leftHandMesh != nullptr);
		//itemToBeHeld->getEquippableActorMesh()->AttachToComponent(leftHandMesh, rules, handGripSocketName);

		itemToBeHeld->getEquippableActorMesh()->AttachToComponent(GetMesh(), rules, leftHandGripSocketName);

		//TODO AttachToSocket on Character Mesh, left hand socket
	}
	else {
		//verifySlow(rightHandMesh != nullptr);
		//itemToBeHeld->getEquippableActorMesh()->AttachToComponent(rightHandMesh, rules, handGripSocketName);

		itemToBeHeld->getEquippableActorMesh()->AttachToComponent(GetMesh(), rules, rightHandGripSocketName);

		//TODO AttachToSotock on Character Mesh, right hand socket
	}
}

void APSCharacter::detachEquippableFromHand(const EHandSpecifier& hand) const {

	if (hand == EHandSpecifier::LEFT_HAND) {

		verifySlow(leftHandCurrentlyHeldItem != nullptr);
		verifySlow(leftHandCurrentlyHeldItem->getEquippableActorMesh() != nullptr);

		leftHandCurrentlyHeldItem->getEquippableActorMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		leftHandCurrentlyHeldItem->SetActorEnableCollision(true);
		leftHandCurrentlyHeldItem->getEquippableActorMesh()->SetSimulatePhysics(true);
	}
	else {
		verifySlow(rightHandCurrentlyHeldItem != nullptr);
		verifySlow(rightHandCurrentlyHeldItem->getEquippableActorMesh() != nullptr);

		rightHandCurrentlyHeldItem->getEquippableActorMesh()->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		rightHandCurrentlyHeldItem->SetActorEnableCollision(true);
		rightHandCurrentlyHeldItem->getEquippableActorMesh()->SetSimulatePhysics(true);
	}
}

UStaticMeshComponent* APSCharacter::getHandMesh(const EHandSpecifier& hand) const {
	
	return hand == EHandSpecifier::LEFT_HAND ? leftHandMesh : rightHandMesh;
}

// Called to bind functionality to input
/*void APSCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}*/

void APSCharacter::tryActvateRightHandItem() {

	useItemOrClenchFist(EHandSpecifier::RIGHT_HAND, rightHandCurrentlyHeldItem);
}

void APSCharacter::tryActivateLeftHandItem() {
	
	useItemOrClenchFist(EHandSpecifier::LEFT_HAND, leftHandCurrentlyHeldItem);
}

void APSCharacter::useItemOrClenchFist(const EHandSpecifier& hand, APSEquippableActor* heldItem) {
	if (heldItem == nullptr) {

		//TODO Possibly turned all of this logic into a HandStateMachine function call
		/* Check if within proximity to pick something up */
		const auto&& optionalEquippableActor = pickupEquippableActorIfAble(hand);

		if(optionalEquippableActor.IsSet()) {
			// Pickup EquippableActor
			setCurrentlyHeldItem(hand, MoveTemp(optionalEquippableActor).GetValue());
			
		}else {
			//Do empty hands stuff, like clenching fist
			//TODO implement clenching fist

			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Nothing to use in hand. Clenching Fist!"));
			}
		}

	}
	else {
		heldItem->use();
	}
}

TOptional<APSEquippableActor*> APSCharacter::pickupEquippableActorIfAble(const EHandSpecifier& hand) {

	
	auto&& optionalEquippableActor = TOptional<APSEquippableActor*>();

	//TODO Implement simplistic collision overlap check

	//TODO Check Hand Animation State Machine to see if it's in potential pickup animation state
	/*if(isHandAnimationControllerInCanPickupState()) {
		
	}*/

	return optionalEquippableActor;
}

bool APSCharacter::isHandAnimationControllerInCanPickupState() {

	//TODO Implement this
	return false;
}

void APSCharacter::tryReloadRightHand() const {

	reloadItemOrDisplayWarning(rightHandCurrentlyHeldItem);
}

void APSCharacter::tryReloadLeftHand() const {  

	reloadItemOrDisplayWarning(leftHandCurrentlyHeldItem);
}

void APSCharacter::reloadItemOrDisplayWarning(APSEquippableActor* heldItem) const {

	if (heldItem == nullptr || !heldItem->IsA(APSWeapon::StaticClass())) {
		//Held item can't be reloaded, do nothing
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Nothing to reload in right hand!"));
		}
	}
	else {
		Cast<APSWeapon>(heldItem)->reload();
	}
}

bool APSCharacter::isHandEmpty(const EHandSpecifier& hand) const {
	if (hand == EHandSpecifier::LEFT_HAND) {
		return leftHandCurrentlyHeldItem == nullptr ? true : false;
	}
	else {
		return rightHandCurrentlyHeldItem == nullptr ? true : false;
	}
}

void APSCharacter::setHandToEmpty(const EHandSpecifier& hand) {

	if (hand == EHandSpecifier::LEFT_HAND) {

		verifySlow(leftHandCurrentlyHeldItem != nullptr);
		leftHandCurrentlyHeldItem->unequip();
		leftHandCurrentlyHeldItem = nullptr;
	}
	else {
		verifySlow(rightHandCurrentlyHeldItem != nullptr);
		rightHandCurrentlyHeldItem->unequip();
		rightHandCurrentlyHeldItem = nullptr;
	}
}

void APSCharacter::setCurrentlyHeldItem(const EHandSpecifier& hand, APSEquippableActor* itemTobeHeld) {
	
	if (hand == EHandSpecifier::LEFT_HAND) {
		verifySlow(leftHandCurrentlyHeldItem == nullptr)
		leftHandCurrentlyHeldItem = itemTobeHeld;
		leftHandCurrentlyHeldItem->equip(this, EHandSpecifier::LEFT_HAND);
	}
	else {
		verifySlow(rightHandCurrentlyHeldItem == nullptr)
		rightHandCurrentlyHeldItem = itemTobeHeld;
		rightHandCurrentlyHeldItem->equip(this, EHandSpecifier::RIGHT_HAND);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "BleedingComponent.h"


// Sets default values for this component's properties
UBleedingComponent::UBleedingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBleedingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	GetOwner()->OnTakePointDamage.AddDynamic(this, &UBleedingComponent::handleEventTakeDamage);
}


// Called every frame
void UBleedingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UBleedingComponent::handleEventTakeDamage(AActor* damagedActor, float damage, AController* instigatedBy, FVector hitLocation, UPrimitiveComponent* fHitComponent, FName boneName, FVector ShotFromDirection, const UDamageType* damageType, AActor* damageCauser) {
	
	// Check material, type of damage, puncture depth, etc.. to see if a wound should be generated on the Actor
	shouldBleed();

	
	if (shouldBleed()) {
		// Create a new flesh wound at the location of the puncture
		createFleshWound();
		notifyWoundCreated();
	}
}

bool UBleedingComponent::shouldBleed() {
	//TODO impl
	return true;
}

void UBleedingComponent::createFleshWound() {
	
	// Determine location/dimensions of the wound to put on the Actor body

	// Determine the depth of the wound

	// Determine if any vital blood-related organs have been hit

	// Determine the intensity at which blood should pour out of the wound

	// Apply flesh wound cosmetics to mesh

	// Calculate intervals and regularity at which to emit blood from the wound

	// Determine type of blood FX to use (drips, gushing, bursting squibs, slow drip, etc...)

	// Set Blood FX emitter Timer for however often to emit blood
}

void UBleedingComponent::applyFleshWoundCosmetics() {
	
	// Attach Blood particle emitter to wound location

	// Play Blood Squib particle FX at the location of the wound

	// Select and Apply laceration/piercing material/texture on Actor mesh
	
}

void UBleedingComponent::setBleedTimer() {
	
	// Get World timer and set Time
}

void UBleedingComponent::notifyWoundCreated() {
	// Notify the Actor or AI
}

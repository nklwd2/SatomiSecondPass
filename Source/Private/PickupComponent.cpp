// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSCharacter.h"
#include "PSEquippableActor.h"
#include "PickupComponent.h"


// Sets default values for this component's properties
UPickupComponent::UPickupComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	bIsActive = false;

	// ...
}


// Called when the game starts
void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	collider = nullptr;

	collider->OnComponentBeginOverlap.AddDynamic(this, &UPickupComponent::handleOnOverlapBegin);
	
}

// Called every frame
void UPickupComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UPickupComponent::handleOnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (isOwnerAnEquippableActor() && isCollidingActorAPlayerCharacter(OtherActor)) {
		//Prompt player that they can pickup/equip actor in HUD/World

		// Set the pickup focus of the player controller to this actor
	}
}

bool UPickupComponent::isCollidingActorAPlayerCharacter(const AActor* collidingActor) const {
	if (collidingActor != nullptr) {
		return collidingActor->GetClass()->IsChildOf(APSCharacter::StaticClass()) ? true : false;
	}
	else {
		return false;
	}
}

bool UPickupComponent::isOwnerAnEquippableActor() const {
	verifySlow(GetOwner() != nullptr);
	return GetOwner()->GetClass()->IsChildOf(APSEquippableActor::StaticClass()) ? true : false;
}

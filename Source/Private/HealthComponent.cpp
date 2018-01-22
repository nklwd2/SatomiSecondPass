// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "HealthComponent.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	if (maxHealth == 0.0){
		maxHealth = 300;
	}

	currentHealth = maxHealth;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Health Initialized!"));
	}

	/* Bind to primary damage notifier for an actor */
	GetOwner()->OnTakePointDamage.AddDynamic(this, &UHealthComponent::handleEventTakeDamage);
}


// Called every frame
void UHealthComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

bool UHealthComponent::isDead() {
	verifySlow(currentHealth >= 0.0f && currentHealth <= maxHealth);
	return currentHealth == minHealth ? true : false;
}

void UHealthComponent::decrementHealth(const float healthToSubtract){
	verifySlow(currentHealth >= 0.0f && currentHealth <= maxHealth);
	currentHealth = FMath::Clamp((currentHealth - healthToSubtract), 0.0f, maxHealth);
}


void UHealthComponent::incrementHealth(const float healthToAdd){
	verifySlow(currentHealth >= 0.0f && currentHealth <= maxHealth);
	currentHealth = FMath::Clamp((currentHealth + healthToAdd), 0.0f, maxHealth);
}

void UHealthComponent::notifyHealthDepleted() {
	OnHealthDepleted.Broadcast();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Actor is dead!"));
	}
}

void UHealthComponent::handleEventTakeDamage(AActor* damagedActor, float damage, class AController* instigatedBy, FVector hitLocation, class UPrimitiveComponent* fHitComponent, FName boneName, FVector ShotFromDirection, const class UDamageType* damageType, AActor* damageCauser) {
	if(!isInvulnerable) {
		takeHealthDamage(damage);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Actor Health decreased!"));
		}
	}
}

float UHealthComponent::takeHealthDamage(const float healthToSubtract) {
	
	if(!isDead()) {
		incrementHealth(healthToSubtract);
		if (isDead()) {
			notifyHealthDepleted();
		}
	}else {
		//This bitch is dead already
	}

	return currentHealth;
}

void UHealthComponent::resetHealthToMax(){

	currentHealth = maxHealth;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "DamageCalculatorAndNotifier.h"


// Sets default values for this component's properties
UDamageCalculatorAndNotifier::UDamageCalculatorAndNotifier()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageCalculatorAndNotifier::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamageCalculatorAndNotifier::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UDamageCalculatorAndNotifier::calculateAndApplyDamageIfApplicable(const FHitResult& hitResult) {
	
	/* Test if the hitresult is an actor and if the actor can be damaged*/
	const auto bShouldDoDamage = shouldDoDamage(hitResult);

	if (bShouldDoDamage) {

		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Damage Calculator Component impl"));
		}

		/* Calculate Damage using stuff */
		const auto damageToApply = calculateDamage(hitResult);

		/* Apply Damage to Actor */
		applyDamage(hitResult, damageToApply);
	}

}

bool UDamageCalculatorAndNotifier::shouldDoDamage(const FHitResult& hitresult)
{
	//TODO impl
	return hitresult.GetActor() != nullptr ? true : false;
}

float UDamageCalculatorAndNotifier::calculateDamage(const FHitResult& hitResult) {
	
	//TODO impl
	return 10.0f;
}

void UDamageCalculatorAndNotifier::applyDamage(const FHitResult& hit, const float damageAmount) const {

	/* Create direct damage event using built-in UE4 damage system,*/
	FPointDamageEvent pointDamage;
	pointDamage.DamageTypeClass = nullptr;//TODO
	pointDamage.HitInfo = hit;
	//pointDamage.ShotDirection = fireDirection;//TODO
	pointDamage.Damage = damageAmount;

	/* Apply damage to actor using built-in UE4 damage system*/
	hit.GetActor()->TakeDamage(pointDamage.Damage, pointDamage, nullptr, nullptr); //TODO get rid of nullptrs
}

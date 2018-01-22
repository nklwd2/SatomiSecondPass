// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSEquippableActor.h"
#include "PSCharacter.h"
#include "PSWeapon.h"
#include "FiringComponent.h"

// Sets default values for this component's properties
UFiringComponent::UFiringComponent(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFiringComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GEngine){
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Firing System initialized!"));
	}

}


// Called every frame
void UFiringComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

FHitResult UFiringComponent::fire() {

	/* Build a full trace line beginning to end*/
	const FVector&& traceStartLocation = getStartingFireLocation();
	//const FRotator&& traceStartRotation = getAdjustedAim(MoveTemp(traceStartLocation));//TODO implement random aiming deviation devia
	//const FVector&& fireDirection = traceStartRotation.Vector();
	const FVector&& fireDirection = getMuzzleDirection();
	const FVector&& traceEndLocation = traceStartLocation + fireDirection * 9000;

	/* Fire off hitscan trace then process results */
	const FHitResult&& hit = hitScanFiringTrace(MoveTemp(traceStartLocation), MoveTemp(traceEndLocation));
	//processInstantHit(MoveTemp(hit), MoveTemp(traceStartLocation), MoveTemp(fireDirection));

	
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PEW"));
	}

	return MoveTemp(hit);

}
 
FVector UFiringComponent::getStartingFireLocation() {
	
	return getMuzzleLocation();
}

FRotator UFiringComponent::getBaseFireRotation() {

	return Cast<APSEquippableActor>(GetOwner())->getOwnerPawn()->GetViewRotation();
}

FRotator UFiringComponent::getAdjustedAim(const FVector & startingFireLocation)
{

	/*FRotator baseAim = getBaseFireRotation();
	//TODO Impl
	if (this) {
	//Calculate Random deviation using spread variables
	return baseAim;
	}
	else {
	// Return the base aim with no randomness applied

	return baseAim;
	}*/

	return FRotator::ZeroRotator;

}

FHitResult UFiringComponent::hitScanFiringTrace(const FVector& StartTrace, const FVector& EndTrace) const
{
	static FName WeaponFireTag(TEXT("WeaponTrace"));


	GetWorld()->DebugDrawTraceTag = WeaponFireTag;

	// Perform trace to retrieve hit info
	auto traceParams = FCollisionQueryParams(WeaponFireTag, true, GetOwner()->Instigator);
	traceParams.bTraceAsyncScene = true;
	traceParams.bReturnPhysicalMaterial = true;
	traceParams.AddIgnoredActor(GetOwner());

	
	auto&& hit = FHitResult(ForceInit);
	GetWorld()->LineTraceSingleByChannel(hit, StartTrace, EndTrace, ECC_GameTraceChannel1, traceParams);

	DrawDebugLine(GetWorld(), StartTrace, hit.Location, FColor(255, 0 ,0), true, 4, 0, 4.0);

	return hit;


}

void UFiringComponent::handleFiring() {

	/*if (m_pMyPawn && m_pMyPawn->IsLocallyControlled()) {
	if (Role < ROLE_Authority) {
	ServerHandleFiring();
	}
	}*/

	//reload after firing last round

	//setuprefire timer
}

void UFiringComponent::processInstantHit(const FHitResult& hit, const FVector& origin, const FVector& fireDirection){

	/* Check if the server holds authority over thing hit with tracer*/
	if (hit.GetActor() && hit.GetActor()->GetRemoteRole() == ROLE_Authority) {

	}
	else if (hit.GetActor() == nullptr){
		if (hit.bBlockingHit) {
			/* Notify server of hit*/
		}
		else {
			/* Notfiy server of miss*/
		}
	}

	/* Process the now server confirmed hit*/
	processConfirmedInstantHit(hit, origin, fireDirection);

}

void UFiringComponent::processConfirmedInstantHit(const FHitResult& hit, const FVector& origin, const FVector& fireDirection)
{

	/* Check whether to deal damage, if so, deal damage*/
	
	/* Play hit impact FX on remote clients*/

	/* Play hit impact FX locally*/

}

bool UFiringComponent::shouldDoDamage(AActor* hitResultActor)
{
	/* Check authority of actor whether to do damamge or not */
	if (hitResultActor && hitResultActor->bCanBeDamaged) {
		if (GetNetMode() != NM_Client || hitResultActor->Role == ROLE_Authority || hitResultActor->bTearOff) {
			return true;
		}
	}

	return false;
}

void UFiringComponent::dealDamage(const FHitResult & hit, const FVector & fireDirection)
{
	/* Create direct damage event using built-in UE4 damage system,*/
	FPointDamageEvent pointDamage;
	pointDamage.DamageTypeClass = nullptr;//fix
	pointDamage.HitInfo = hit;
	pointDamage.ShotDirection = fireDirection;
	//pointDamage.Damage = nullptr;//fix

	/* Apply damage to actor using built-in UE4 damage system*/
	//hit.GetActor()->TakeDamage(pointDamage.Damage, pointDamage, m_pMyPawn, this);
}

FVector UFiringComponent::getMuzzleLocation() const{
	return Cast<APSWeapon>(GetOwner())->getEquippableActorMesh()->GetSocketLocation(MuzzleAttachPoint);
}

FVector UFiringComponent::getMuzzleDirection() const{
	return Cast<APSWeapon>(GetOwner())->getEquippableActorMesh()->GetSocketRotation(MuzzleAttachPoint).Vector();
}

bool UFiringComponent::ServerHandleFiring_Validate(void) {
	
	return true;
}

void UFiringComponent::ServerHandleFiring_Implementation(void) {
	//TODO Impl
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSEquippableActor.h"
#include "AmmoClipSystemComponent.h"

UAmmoClipSystemComponent::UAmmoClipSystemComponent(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	//Cast<APSEquippableActor>(GetOwner())->RegisterSubscriptionsAndPublications<UAmmoClipSystemComponent>(subscriptions, publications);
}

// Called when the game starts
void UAmmoClipSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	setClipAmount(MaxClipSize);
	setAmmoReserveAmount(StartingAmmoReserveAmount);
	setClipsInReserveAmount(StartingNumberOfClipsInReserve);

	if (GEngine){
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Ammo initialized!"));
	}
}


// Called every frame
void UAmmoClipSystemComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

bool UAmmoClipSystemComponent::tryReload(){
	if (canReload()){
		reloadAmmoSystem();
		return true;
	}
	else{
		return false;
	}
}

bool UAmmoClipSystemComponent::tryConsumeAmmo(){
	if (canConsumeAmmo()){
		decrementClipAmountByCost();
		return true;
	}
	else{
		//Trigger CAn't Fire Event 
		return false;
	}
}

bool UAmmoClipSystemComponent::canReload(){

	if (!isAmmoReserveEmpty() && !isAmmoClipFull() && FMath::Clamp(CurrentAmmoInReserve - MaxClipSize, 0, MaxClipSize) >= 0){
		return true;
	}
	else{
		return false;
	}
}

bool UAmmoClipSystemComponent::canConsumeAmmo(void){

	if (isAmmoClipEmpty() != true && FMath::Clamp(CurrentClipAmount - AmmoCostPerUse, 0, MaxClipSize) >= 0){
		return true;
	}
	else{
		return false;
	}

}

bool UAmmoClipSystemComponent::isAmmoClipFull(){
	return CurrentClipAmount == MaxClipSize ? true : false;
}

bool UAmmoClipSystemComponent::isAmmoClipEmpty(){
	return CurrentClipAmount == 0 ? true : false;
}

bool UAmmoClipSystemComponent::isAmmoReserveEmpty(){
	return CurrentAmmoInReserve == 0 ? true : false;
}

void UAmmoClipSystemComponent::reloadAmmoSystem(){

	decrementAmmoReserveByClip();
	resetAmmoClipToMax();

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Reloaded"));
	}

}

void UAmmoClipSystemComponent::decrementClipAmountByCost(){

	if (FMath::Clamp(CurrentClipAmount - AmmoCostPerUse, 0, MaxClipSize) >= 0){
		CurrentClipAmount -= AmmoCostPerUse;
	}
	else{
		//no more bullets, perhaps take conditional out and just use clamp
	}
}

void UAmmoClipSystemComponent::incrementClipAmountByCost(void){

	if (FMath::Clamp(CurrentClipAmount + AmmoCostPerUse, 0, MaxClipSize) <= MaxClipSize){
		CurrentClipAmount += AmmoCostPerUse;
	}
	else{
		//At max clip size, perhaps take conditional out and just use clamp
	}
}


void UAmmoClipSystemComponent::decrementAmmoReserveByClip(void){

	if ((FMath::Clamp(CurrentAmmoInReserve - MaxClipSize, 0, MaxNumberOfAmmoInReserve)) >= 0){
		CurrentAmmoInReserve -= MaxClipSize;
	}
	else{
		//Not enough ammo to fire! Cannot decrement ammo reserve by clip
	}
}

void UAmmoClipSystemComponent::incrementAmmoReserveByClip(void){

	if (FMath::Clamp(CurrentAmmoInReserve + MaxClipSize, 0, MaxNumberOfAmmoInReserve) <= MaxNumberOfAmmoInReserve){
		CurrentAmmoInReserve += MaxClipSize;
	}
	else{
		//At max ammo in reserve, cannot increment further
	}
}


void UAmmoClipSystemComponent::decrementAmmoReserveByCost(void){

	if (FMath::Clamp(CurrentAmmoInReserve - AmmoCostPerUse, 0, MaxNumberOfAmmoInReserve) >= 0){
		CurrentAmmoInReserve -= AmmoCostPerUse;
	}
	else{
		//error
	}
}


void UAmmoClipSystemComponent::incrementAmmoReserveByCost(void){

	if (FMath::Clamp(CurrentAmmoInReserve + AmmoCostPerUse, 0, MaxNumberOfAmmoInReserve) <= MaxNumberOfAmmoInReserve){
		CurrentAmmoInReserve += AmmoCostPerUse;
	}
	else{
		//At max ammo in reserve, 
	}
}

void UAmmoClipSystemComponent::incrementClipReserveAmount(void){
	if (CurrentClipsInReserve != MaxNumberOfClipsInReserve){
		CurrentClipsInReserve += 1;
	}
	else{
		//At maximum number of clips allowed in reserve
	}
}

void UAmmoClipSystemComponent::decrementClipReserveAmount(void){

	if (CurrentClipsInReserve > 0){
		CurrentClipsInReserve -= 1;
	}
	else{
		//no clips remaining in reserve
	}


}

void UAmmoClipSystemComponent::setClipAmount(int32 amountToSetClipTo){

	if (FMath::Clamp(amountToSetClipTo, 0, MaxClipSize) <= MaxClipSize){
		CurrentClipAmount = amountToSetClipTo;
	}
	else{
		//Cannot set ammo clip to supplied amount!
	}

}

void UAmmoClipSystemComponent::setAmmoReserveAmount(int32 amountToSetReserveTo){

	CurrentAmmoInReserve = FMath::Clamp(amountToSetReserveTo, 0, MaxNumberOfAmmoInReserve);
}

void UAmmoClipSystemComponent::setClipsInReserveAmount(int32 amountToSetClipTo){

}

void UAmmoClipSystemComponent::resetAmmoClipToMax(){

	CurrentClipAmount = MaxClipSize;
}

void UAmmoClipSystemComponent::resetAmmoReserveToMax(){

	CurrentAmmoInReserve = MaxNumberOfAmmoInReserve;
}

void UAmmoClipSystemComponent::resetClipReserveToMax(){

	CurrentClipsInReserve = MaxNumberOfClipsInReserve;
}
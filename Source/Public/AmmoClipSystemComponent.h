// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "AmmoClipSystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FAmmoConsumedEvent);
DECLARE_MULTICAST_DELEGATE(FOutOfAmmoEvent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSATOMI_API UAmmoClipSystemComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:
	
	FAmmoConsumedEvent* OnAmmoConsumed;

	FOutOfAmmoEvent OnOutOfAmmo;

	UPROPERTY(EditDefaultsOnly, Category = Events)
	FName AmmoConsumedEventName;

	UPROPERTY(EditDefaultsOnly, Category = Events)
	FName OutOfAmmoEventName;

	UPROPERTY(EditDefaultsOnly,  Category = "Ammo System")
	int32 MaxNumberOfAmmoInReserve;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo System")
	int32 MaxNumberOfClipsInReserve;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo System")
	int32 MaxClipSize;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo System")
	int32 AmmoCostPerUse;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo System")
	int32 StartingAmmoReserveAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo System")
	int32 StartingNumberOfClipsInReserve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo System")
	bool IsUsingReservePool;


private:

	int32 CurrentClipAmount;
	int32 CurrentAmmoInReserve;
	int32 CurrentClipsInReserve;

public:
	// Sets default values for this component's properties
	UAmmoClipSystemComponent();

/*	virtual void SubscribeToEventAggregatorDependencies();

	virtual void PublishEventsToEventAggregators();*/

	// Called when the game starts
	void BeginPlay() override;
	
	// Called every frame
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Public Facing Ammo Component API

	bool tryReload();

	bool tryConsumeAmmo();

	bool canConsumeAmmo();

	bool canReload();

	void reloadAmmoSystem();

private:
	// Conditional use case checking

	bool isAmmoClipEmpty();

	bool isAmmoClipFull();

	bool isAmmoReserveEmpty();

	//Incrementing and Decrementing methods

	void decrementClipAmountByCost();

	void incrementClipAmountByCost();

	void decrementAmmoReserveByClip();
	
	void incrementAmmoReserveByClip(); 

	void decrementAmmoReserveByCost();

	void incrementAmmoReserveByCost();

	void decrementClipReserveAmount();

	void incrementClipReserveAmount();


	// Specific setters for ammo storage variables

	void setClipAmount(int32 amountToSetClipTo);

	void setAmmoReserveAmount(int32 amountToSetReserveTo);

	void setClipsInReserveAmount(int32 amountToSetReserveTo);

	// Methods for setting ammo storage containers to max value

	void resetAmmoClipToMax();

	void resetAmmoReserveToMax();
	
	void resetClipReserveToMax();

};

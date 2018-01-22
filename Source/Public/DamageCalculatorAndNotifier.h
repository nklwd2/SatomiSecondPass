// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DamageCalculatorAndNotifier.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSATOMI_API UDamageCalculatorAndNotifier : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageCalculatorAndNotifier();

	// Called when the game starts
	void BeginPlay() override;
	
	// Called every frame
	void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void calculateAndApplyDamageIfApplicable(const FHitResult& hitResult);

	virtual bool shouldDoDamage(const FHitResult& hitResult);
		
	virtual float calculateDamage(const FHitResult& hitResult);

	void applyDamage(const FHitResult& victim, const float damageAmount) const;
	
};

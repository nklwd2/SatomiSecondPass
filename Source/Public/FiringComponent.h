// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FiringComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAmmoConsumedSignature);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSATOMI_API UFiringComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()
public:


	UPROPERTY(BlueprintAssignable, Category="Firing")
	FOnAmmoConsumedSignature OnAmmoConsumed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<float> Spread;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (ClampMin = "0.1"))
	TArray<float> FireRate;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<USoundBase*> FireSound;

	/** How much spread increases for each shot */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enforcer)
	float SpreadIncrease;

	/** Max spread  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enforcer)
	float MaxSpread;

	/** Last time a shot was fired (used for calculating spread). */
	UPROPERTY(BlueprintReadWrite, Category = Enforcer)
	float LastFireTime;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float maxTraceRange;

	UPROPERTY()
	USkeletalMeshComponent* cachedParentMesh;

	/** name of bone/socket for muzzle in skeletal mesh */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	FName MuzzleAttachPoint = FName(TEXT("Fire_FX_Slot"));

	/** FX for muzzle flash */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
	class UParticleSystem* MuzzleFX;

	/** spawned component for muzzle FX */
	UPROPERTY(Transient)
	class UParticleSystemComponent* MuzzleParticleSystemComponent;

public:	
	// Sets default values for this component's properties
	UFiringComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	virtual FHitResult fire(void);

	//ShooterDemo
	UFUNCTION(reliable, server, WithValidation)
	void ServerHandleFiring();

	//Shooter demo
	void handleFiring();

	FVector getStartingFireLocation();

	FRotator getBaseFireRotation();

	FRotator getAdjustedAim(const FVector& startingFireLocation);

	FVector getMuzzleLocation() const;

	/*
	*/
	FVector getMuzzleDirection() const;

	/*
	*/
	FHitResult hitScanFiringTrace(const FVector& TraceFron, const FVector& TraceTo) const;

	void processInstantHit(const FHitResult& hit, const FVector& origin, const FVector& fireDirection );

	void processConfirmedInstantHit(const FHitResult& hit, const FVector& origin, const FVector& fireDirection);

	bool shouldDoDamage(AActor* hitResultActor);

	void dealDamage(const FHitResult& hit, const FVector& fireDirection);
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthDepletedNotification);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSATOMI_API UHealthComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	float currentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config)
	float maxHealth;

	const float minHealth = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Config)
	bool isInvulnerable;


	UPROPERTY(BlueprintAssignable, Category = "Test")
	FHealthDepletedNotification OnHealthDepleted;

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	// Called when the game starts
	void BeginPlay() override;
	
	// Called every frame
	void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual bool isDead();
		
	void decrementHealth(const float healthToSubtract);

	void incrementHealth(const float healthToAdd);
	void notifyHealthDepleted();

	virtual float takeHealthDamage(const float healthToSubtract);

	void resetHealthToMax();

	UFUNCTION()
	void handleEventTakeDamage(AActor* damagedActor, float damage, class AController* instigatedBy, FVector hitLocation, class UPrimitiveComponent* fHitComponent, FName boneName, FVector ShotFromDirection, const class UDamageType* damageType, AActor* damageCauser);
};

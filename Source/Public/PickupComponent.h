// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PickupComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTSATOMI_API UPickupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UPrimitiveComponent* collider;

	// Sets default values for this component's properties
	UPickupComponent();

	// Called when the game starts
	void BeginPlay() override;
	
	// Called every frame
	void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void handleOnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool isCollidingActorAPlayerCharacter(const AActor* collidingActor) const;
	
	bool isOwnerAnEquippableActor() const;

	bool bIsActive;
	
};

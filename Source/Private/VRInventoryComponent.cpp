// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "VRInventoryComponent.h"


// Sets default values for this component's properties
UVRInventoryComponent::UVRInventoryComponent(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// Initialize Hands
	//InventoryArray.Init(5);
	// ...
}


// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "UseableActor.h"


// Sets default values
AUseableActor::AUseableActor(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUseableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUseableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AUseableActor::use(){

}
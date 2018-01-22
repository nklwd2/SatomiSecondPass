// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectSatomi.h"
#include "PSBodyTypes.h"
#include "Runtime/Engine/Classes/Components/SplineComponent.h"
#include "PSEquippableActor.h"


// Sets default values
APSEquippableActor::APSEquippableActor(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	equippableActorMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ThirdPersonEquippableActorModel"));
	equippableActorMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	getEquippableActorMesh()->SetSimulatePhysics(true);

	VRsplineGripComponent = ObjectInitializer.CreateDefaultSubobject<USplineComponent>(this, TEXT("VRSplineGripComponent"));
	VRsplineGripComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	equippableActorOwner = nullptr;
	bodyPartEquippedTo = EHandSpecifier::NON_APPLICABLE;

}

// Called when the game starts or when spawned
void APSEquippableActor::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void APSEquippableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void APSEquippableActor::equip(APSCharacter* newOwner, const EHandSpecifier &bodyPartToEquipTo){

	verifySlow(newOwner != nullptr);
	verifyf(equippableActorOwner == nullptr, TEXT("The EquippableActor already is equipped to something!"));
	verifySlow(bodyPartToEquipTo != EHandSpecifier::NON_APPLICABLE);

	equippableActorOwner = newOwner;
	bodyPartEquippedTo = bodyPartToEquipTo;

	verifyf(equippableActorOwner !=  nullptr, TEXT("The EquippableActor has been accidently equipped to nothing! (Null)"));
}

void APSEquippableActor::unequip(){

	verifySlow(equippableActorOwner != nullptr);
	verifySlow(bodyPartEquippedTo != EHandSpecifier::NON_APPLICABLE);

	equippableActorOwner = nullptr;
	bodyPartEquippedTo = EHandSpecifier::NON_APPLICABLE;
}
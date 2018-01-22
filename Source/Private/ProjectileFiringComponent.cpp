// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "ProjectileFiringComponent.h"

UProjectileFiringComponent::UProjectileFiringComponent(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{


}

FHitResult UProjectileFiringComponent::fire(void) {
	return FHitResult();
}


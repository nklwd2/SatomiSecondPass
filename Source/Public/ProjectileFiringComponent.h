// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FiringComponent.h"
#include "ProjectileFiringComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSATOMI_API UProjectileFiringComponent : public UFiringComponent
{
	GENERATED_UCLASS_BODY()
	
	

	UProjectileFiringComponent();
	
	virtual FHitResult fire(void) override;
};

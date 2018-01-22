// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FiringComponent.h"
#include "HitscanFiringComponent.generated.h"

/**
 * 
 */


UCLASS()
class PROJECTSATOMI_API UHitscanFiringComponent : public UFiringComponent
{
	GENERATED_UCLASS_BODY()
	

	UHitscanFiringComponent();
	
	virtual FHitResult fire() override;
	

};



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PSCharacter.h"
#include "PSNonVRCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSATOMI_API APSNonVRCharacter : public APSCharacter
{
	GENERATED_UCLASS_BODY()

	void initializePlayerHands();
	
};

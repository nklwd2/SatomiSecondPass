// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameObjective.h"
#include "GOKillDesignatedPerson.generated.h"

class APSCharacter;


UCLASS(CustomConstructor)
class PROJECTSATOMI_API UGOKillDesignatedPerson : public UGameObjective
{
	GENERATED_UCLASS_BODY()

	UGOKillDesignatedPerson(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer) {
	}

public:

	class APSCharacter* characterToKill;

	
	void onGameObjectiveStarted() override;

	void initializeKillDesignatedPersonObjective(class APSCharacter* characterToTarget);
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "GameGoal.generated.h"

class UGameObjective;

/**
 * 
 */

USTRUCT()
struct FGameGoalStep
{
	GENERATED_USTRUCT_BODY()

	class UGameObjective* gameObjectiveToBeCompleted;

	bool isCompleted = false;

};

UCLASS(CustomConstructor)
class PROJECTSATOMI_API UGameGoal : public UObject
{

	GENERATED_UCLASS_BODY()

	UGameGoal(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
	{}



	TArray<FGameGoalStep> requiredStepsForCompletion;


	virtual void OnGameGoalStarted();

	virtual void OnGameGoalCompleted();

	bool isGameGoalCompleted();



	
};

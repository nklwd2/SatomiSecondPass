// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "GameObjective.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FObjectiveCompletedDelegate);

/**
 * 
 */
UCLASS(CustomConstructor)
class PROJECTSATOMI_API UGameObjective : public UObject
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintAssignable, Category = "Test")
	FObjectiveCompletedDelegate onObjectiveCompletedNotifier;

	bool isObjectiveCompleted = false;
	
	UGameObjective(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
	{}
	
	virtual void onGameObjectiveStarted();

	UFUNCTION()
	void onGameObjectiveCompleted();

	bool isGameObjectiveCompleted();

	virtual void  evaluateObjectiveCompletionCriteria();


	
};

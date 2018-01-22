// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "GameGoal.h"

void UGameGoal::OnGameGoalStarted() {}

void UGameGoal::OnGameGoalCompleted() {}

bool UGameGoal::isGameGoalCompleted() {
	
	uint8 completedObjectiveCount = 0;
	for(auto&& gameobjective : requiredStepsForCompletion) {
		
		gameobjective.isCompleted ? completedObjectiveCount++ : completedObjectiveCount;
	}

	return completedObjectiveCount == requiredStepsForCompletion.Num() ? true : false;
}

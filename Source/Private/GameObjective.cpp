// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "GameObjective.h"

void UGameObjective::onGameObjectiveStarted() {}

void UGameObjective::onGameObjectiveCompleted() {
	
	onObjectiveCompletedNotifier.Broadcast();
}

bool UGameObjective::isGameObjectiveCompleted() {
	
	return isObjectiveCompleted;

}

void UGameObjective::evaluateObjectiveCompletionCriteria() {
	
}

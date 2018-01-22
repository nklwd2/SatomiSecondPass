// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSCharacter.h"
#include "GOKillDesignatedPerson.h"

void UGOKillDesignatedPerson::onGameObjectiveStarted() {
	characterToKill->onCharacterDeathNotifier.AddDynamic(this, &UGOKillDesignatedPerson::onGameObjectiveCompleted);

}

void UGOKillDesignatedPerson::initializeKillDesignatedPersonObjective(APSCharacter* characterToTarget) {
	
	characterToKill = characterToTarget;
	onGameObjectiveStarted();
}

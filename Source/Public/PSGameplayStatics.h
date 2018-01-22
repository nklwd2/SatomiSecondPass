// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "PSGameplayStatics.generated.h"

class UUserWidget;

/**
 * 
 */
UCLASS()
class PROJECTSATOMI_API UPSGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
	
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UUserWidget> textWidgetClass;*/
	
	FTimerHandle despawnTimerHandle;
	
	UFUNCTION(BlueprintCallable, Category = Debug)
	static void spawnDebugTextAtLocation(const FString& debugTextToSpawn, const FColor& textColor, const uint8 textSize, const float duration, const FVector& locationToSpawnAt, UWorld* world, APlayerController* playerController, TSubclassOf<UUserWidget> textWidgetClass);


	//TODO Implement function for Spawning Text over Duration

	//TODO Implement function for Spawning Text with momentum

};

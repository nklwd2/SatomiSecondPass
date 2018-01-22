// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "DebugTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTSATOMI_API UDebugTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	FText debugText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	FLinearColor textColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	uint8 textSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	float duration;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	FVector widgetLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Properties)
	APlayerController* playerController;
};

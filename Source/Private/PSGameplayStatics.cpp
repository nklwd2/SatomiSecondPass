// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSGameplayStatics.h"
#include "DebugTextWidget.h"
#include "UserWidget.h"

UPSGameplayStatics::UPSGameplayStatics(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer) {
	/*static ConstructorHelpers::FClassFinder<UUserWidget> widget(TEXT("/Game/ProjectSatomi/UI/Debug/DebugVRText/DebugTextWidget"));

	textWidgetClass = widget.Class;*/
}

void UPSGameplayStatics::spawnDebugTextAtLocation(const FString& debugTextToSpawn, const FColor& textColor, const uint8 textSize, const float duration, const FVector& locationToSpawnAt,  UWorld* world, APlayerController* playerController, TSubclassOf<UUserWidget> textWidgetClass) {
	

	
	auto&& debugTextWidget = CreateWidget<UDebugTextWidget>(world, textWidgetClass);

	debugTextWidget->debugText = FText::FromString(debugTextToSpawn);
	debugTextWidget->widgetLocation = locationToSpawnAt;
	debugTextWidget->textColor = FLinearColor(textColor);
	debugTextWidget->textSize = textSize;
	debugTextWidget->duration = duration;
	debugTextWidget->playerController = playerController;
	debugTextWidget->AddToViewport();

}

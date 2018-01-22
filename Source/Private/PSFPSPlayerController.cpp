// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectSatomi.h"
#include "PSCharacter.h"
#include "PSBodyTypes.h"
#include "PSFPSPlayerController.h"
#include "PSVRCharacter.h"

APSFPSPlayerController::APSFPSPlayerController(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

//	PSCharacter = new APSCharacter();

//	AController::SetPawn(PSCharacter);

	PSCharacter = Cast<APSCharacter>(GetCharacter());

}

void APSFPSPlayerController::SetupPlayerState(){

	//Cast to Local player then null checl player state, then set chat destination?

}

void APSFPSPlayerController::SetName(const FString& s){

}

void APSFPSPlayerController::ExecShowMenu(){

	ShowMenu(TEXT(""));
}

void APSFPSPlayerController::ShowMenu(const FString& s){

	//Cast to Local player, check if null then show menu to local player


}

void APSFPSPlayerController::HideMenu(){

	//Cast to local Player, check if null then hide menu through local player
}

void APSFPSPlayerController::Talk(){


	//Cast to local player nullcheck and nullcheck ViewPort Client, StartTyping through Viewport


}

void APSFPSPlayerController::TeamTalk(){
	//Cast to local player nullcheck and nullcheck ViewPort Client, StartTyping through Viewport

}

void APSFPSPlayerController::Say(FString message){

	//check message length then if AllowTestMessage, ServerSay and ClientSay_Implmementation
}

void APSFPSPlayerController::TeamSay(FString message){
	//check message length then if AllowTestMessage, ServerSay and ClientSay_Implmementation
}

uint8 APSFPSPlayerController::GetTeamNum() const {

	return 1;
}


void APSFPSPlayerController::SetupInputComponent(){

	Super::SetupInputComponent();

	InputComponent->BindAction("ShowMenu", IE_Released, this, &APSFPSPlayerController::ExecShowMenu);

	InputComponent->BindAction("Jump", IE_Pressed, this, &APSFPSPlayerController::OnInputJump);
	InputComponent->BindAxis("MoveForward", this, &APSFPSPlayerController::OnInputMoveForward);
	InputComponent->BindAxis("MoveBackward", this, &APSFPSPlayerController::OnInputMoveBackward);
	InputComponent->BindAxis("MoveRight", this, &APSFPSPlayerController::OnInputMoveRight);
	InputComponent->BindAxis("MoveLeft", this, &APSFPSPlayerController::OnInputMoveLeft);

	InputComponent->BindAxis("Turn", this, &APlayerController::AddYawInput);
	InputComponent->BindAxis("TurnRate", this, &APSFPSPlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APlayerController::AddPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &APSFPSPlayerController::LookUpAtRate);

	InputComponent->BindAction("ToggleCamera", IE_Pressed, this, &APSFPSPlayerController::OnInputToggleCamera);

	InputComponent->BindAction("FireRightHandWeapon", IE_Pressed, this, &APSFPSPlayerController::OnInputFireRightHandWeapon);
	InputComponent->BindAction("FireLeftHandWeapon", IE_Pressed, this, &APSFPSPlayerController::OnInputFireLeftHandWeapon);

	InputComponent->BindAction("ReloadRightHand", IE_Pressed, this, &APSFPSPlayerController::OnInputReloadRight);
	InputComponent->BindAction("ReloadLeftHand", IE_Pressed, this, &APSFPSPlayerController::OnInputReloadLeft);

	InputComponent->BindAction("ControllerReload", IE_Pressed, this, &APSFPSPlayerController::OnInputAltReloadPressed);
	InputComponent->BindAction("ControllerReload", IE_Released, this, &APSFPSPlayerController::OnInputAltReloadReleased);

	InputComponent->BindAction("Punch", IE_Pressed, this, &APSFPSPlayerController::OnInputPunchPressed);
	InputComponent->BindAction("Punch", IE_Released, this, &APSFPSPlayerController::OnInputPunchReleased);

	InputComponent->BindAction("PickupItemRightHand", IE_Pressed, this, &APSFPSPlayerController::OnInputPickupItemRightHand);
	InputComponent->BindAction("PickupItemLeftHand", IE_Pressed, this, &APSFPSPlayerController::OnInputPickupItemLeftHand);

	InputComponent->BindAction("LetGoItemRightHand", IE_Released, this, &APSFPSPlayerController::OnInputLetGoItemRightHand);
	InputComponent->BindAction("LetGoItemLeftHand", IE_Released, this, &APSFPSPlayerController::OnInputLetGoItemLeftHand);
}

void APSFPSPlayerController::OnInputToggleCamera()
{

	if (PSCharacter) {
		PSCharacter->ToggleCamera();
	}
}


void APSFPSPlayerController::OnInputJump(void){

	if (PSCharacter != nullptr && !IsMoveInputIgnored()){
		UE_LOG(LogTemp, Log, TEXT("Jump"));
		PSCharacter->Jump();
	}
	
}

void APSFPSPlayerController::OnInputMoveForward(float Value)
{

	if (Value != 0.0f && PSCharacter != nullptr){

		PSCharacter->MoveForward(Value);
	}
}

void APSFPSPlayerController::OnInputMoveBackward(float Value){

	OnInputMoveForward(Value * -1);
}

void APSFPSPlayerController::OnInputMoveRight(float Value){

	if (Value != 0.0f && PSCharacter != nullptr){
		PSCharacter->MoveRight(Value);
	}

}

void APSFPSPlayerController::OnInputMoveLeft(float Value){

	OnInputMoveRight(Value * -1);
}

void APSFPSPlayerController::TurnAtRate(float Value){

}

void APSFPSPlayerController::LookUpAtRate(float Value){

}

void APSFPSPlayerController::OnInputFireRightHandWeapon(){

	if (PSCharacter != nullptr){

		PSCharacter->tryActvateRightHandItem();
	}
}

void APSFPSPlayerController::OnInputFireLeftHandWeapon(){
	if (PSCharacter != nullptr){

		PSCharacter->tryActivateLeftHandItem();
	}
}

void APSFPSPlayerController::OnInputReloadRight(){

	if (PSCharacter != nullptr){

		PSCharacter->tryReloadRightHand();
	}
}

void APSFPSPlayerController::OnInputReloadLeft(){
	if (PSCharacter != nullptr){

		PSCharacter->tryReloadLeftHand();
	}
}

void APSFPSPlayerController::OnInputAltReloadPressed(){

}

void APSFPSPlayerController::OnInputAltReloadReleased(){

}

/*Shit code just for tutorial, will remove */

void APSFPSPlayerController::OnInputPunchPressed(){

	isPunching = true;
}

void APSFPSPlayerController::OnInputPunchReleased(){

	isPunching = false;
}

void APSFPSPlayerController::OnInputPickupItemRightHand()
{

	auto&& optionalPickupItem  = Cast<APSVRCharacter>(PSCharacter)->pickupEquippableActorIfAble(EHandSpecifier::RIGHT_HAND);
	if(optionalPickupItem.IsSet()) {
		PSCharacter->tryEquipHand(EHandSpecifier::RIGHT_HAND, optionalPickupItem.GetValue());
	}
}

void APSFPSPlayerController::OnInputPickupItemLeftHand()
{
	auto&& optionalPickupItem = Cast<APSVRCharacter>(PSCharacter)->pickupEquippableActorIfAble(EHandSpecifier::LEFT_HAND);
	if (optionalPickupItem.IsSet()) {
		PSCharacter->tryEquipHand(EHandSpecifier::LEFT_HAND, optionalPickupItem.GetValue());
	}
}

void APSFPSPlayerController::OnInputLetGoItemRightHand()
{
	//Drop Item
	PSCharacter->tryUnequipHand(EHandSpecifier::RIGHT_HAND);
}

void APSFPSPlayerController::OnInputLetGoItemLeftHand()
{
	//Drop Item
	PSCharacter->tryUnequipHand(EHandSpecifier::LEFT_HAND);
}

APSCharacter* APSFPSPlayerController::GetPSCharacter()
{
	return PSCharacter;
}

void APSFPSPlayerController::SetPawn(APawn* InPawn)
{

	AController::SetPawn(InPawn);

	PSCharacter = Cast<APSCharacter>(InPawn);
}


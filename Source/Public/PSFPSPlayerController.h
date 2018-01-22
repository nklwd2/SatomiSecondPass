// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PSFPSPlayerController.generated.h"

class APSPlayerState;

/**
 * 
 */
UCLASS()
class PROJECTSATOMI_API APSFPSPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

private:

	UPROPERTY()
	APSCharacter* PSCharacter;

	UPROPERTY()
	APSPlayerState* cachedPlayerState;

	bool rightHandOccupied;
	bool leftHandOccupied;

	UPROPERTY()
	APSEquippableActor* currentPlayerPickupFocus;

	void SetupPlayerState();

	virtual void SetName(const FString& name) override;

	UFUNCTION(exec, BlueprintCallable, Category = "UI")
	virtual void ShowMenu(const FString& s);

	virtual void ExecShowMenu();

	UFUNCTION(exec)
	virtual void HideMenu();

	UFUNCTION()
	virtual void Talk(); //not implemented

	UFUNCTION()
	virtual void TeamTalk();

	UFUNCTION(exec)
	virtual void Say(FString message);

	UFUNCTION(exec)
	virtual void TeamSay(FString message);

	/*UFUNCTION(reliable, server, WithValidation)
	virtual void ServerSay(const FString& message, bool IsTeamMessage);

	UFUNCTION(reliable, client)
	virtual void ClientSay();*/

	//if ~PSServer
	// virtual void ShowMessage()
	//endif

	uint8 GetTeamNum() const;



protected:

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Current movement axis deflecton forward/back (back is negative) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementForwardAxis;

	/** Current movement axis deflecton right/left (left is negative) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float MovementStrafeAxis;


	

public:

	void SetupInputComponent() override;

	/* Weapon Related Inputs*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	bool isPunching;


protected:

	UFUNCTION(BlueprintCallable, Category = PlayerController)
	virtual APSCharacter* GetPSCharacter();

	virtual void SetPawn(APawn* InPawn);


	void OnInputToggleCamera(void);

	/* Movement Related Inputs*/

	void OnInputMoveForward(float value);
	void OnInputMoveBackward(float value);
	void OnInputMoveLeft(float value);
	void OnInputMoveRight(float value);

	/* Aiming*/
	void TurnAtRate(float value);
	void LookUpAtRate(float value);

	void OnInputJump();

	void OnInputFireRightHandWeapon();
	void OnInputFireLeftHandWeapon();

	void OnInputReloadRight();
	void OnInputReloadLeft();
	void OnInputAltReloadPressed();
	void OnInputAltReloadReleased();

	/* Shit code just for tutorial, will remove */
	void OnInputPunchPressed();
	void OnInputPunchReleased();

	void OnInputPickupItemRightHand();
	void OnInputPickupItemLeftHand();
	
	void OnInputLetGoItemRightHand();
	void OnInputLetGoItemLeftHand();

	//virtual void Possess(APawn* PawnToPossess) override;

	
};

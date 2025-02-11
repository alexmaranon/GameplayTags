// Copyright Epic Games, Inc. All Rights Reserved.

#include "UTHUB_GAS_T1GameMode.h"
#include "UTHUB_GAS_T1PlayerController.h"
#include "UTHUB_GAS_T1Character.h"
#include "UObject/ConstructorHelpers.h"

AUTHUB_GAS_T1GameMode::AUTHUB_GAS_T1GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUTHUB_GAS_T1PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
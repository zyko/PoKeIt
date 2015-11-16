// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameFramework/PlayerController.h"
#include "PlayerPoker.generated.h"

/**
 * 
 */
UCLASS()
class POKEIT_API APlayerPoker : public APlayerController
{
	GENERATED_BODY()
			

public:

	/**
	* UPROPERTY and UFUNCTIONE make the variables and functions to appear in blueprints
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "chips")
		int32 chips;

	APlayerPoker();


	UFUNCTION(BlueprintCallable, Category = "chips")
		void increaseChips();


	// Card hand[2];

	void receiveCards();

	void callRound();

	void checkRound();

	void raiseRound();

	void foldRound();


	
	
};

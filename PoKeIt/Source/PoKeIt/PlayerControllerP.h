// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PlayerP.h"
#include "PlayerControllerP.generated.h"


class PlayerP;

/**
 * 
 */
UCLASS()
class POKEIT_API APlayerControllerP : public APlayerController
{
	GENERATED_BODY()


public:

	/**
	* UPROPERTY and UFUNCTION make the variables and functions to appear in blueprints
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "chips")
		int32 chips;

	/*
	// PlayerP players[8];
	//UFUNCTION(BlueprintCallable, Category = "chips")
	void createPlayers(int);
	*/

	APlayerControllerP();


	UFUNCTION(BlueprintCallable, Category = "chips")
		void increaseChips();


	// Card hand[2];

	void receiveCards();

	void callRound();

	void checkRound();

	void raiseRound();

	void foldRound();


	
};

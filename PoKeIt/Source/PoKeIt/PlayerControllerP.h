// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "PlayerP.h"
#include "PlayerControllerP.generated.h"


//class APlayerP;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "chips")
		int32 currentPlayersChips=0;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "players")
	//	int32 amountOfPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "players")
		int32 currentPlayer=0;


	UFUNCTION(BlueprintCallable, Category = "players")
		void spawnPlayers(int32 amountOfPlayersSelected);

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void foldRound();

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void betRaise(APlayerP* p1, APlayerP* p2);


	void updateCurrentPlayersChips();

	void finishTurn();


//	APlayerP* players [8];
	

	APlayerControllerP();



	UFUNCTION(BlueprintCallable, Category = "chips")
		void increaseChips();


	// Card hand[2];

	void receiveCards();

	void callRound();

	void checkRound();

	

//	void foldRound();


	
};

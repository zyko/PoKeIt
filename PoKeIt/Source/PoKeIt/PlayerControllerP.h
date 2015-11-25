// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/PlayerController.h"
#include "MyPlayerP.h"
#include "Card.h"
#include "RoundManager.h"
#include "PlayerControllerP.generated.h"


class RoundManager;

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


	// variables:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "chips")
		int32 chips;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "chips")
		int32 currentPlayersChips=0;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "players")
	//	int32 amountOfPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "players")
		int32 currentPlayer=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "round management")
		int32 potSize=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 cardColor0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 cardValue0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 cardColor1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 cardValue1;




	MyPlayerP* players[8];
	RoundManager* roundManager;
	Card* currentPlayersHand[2];


	// functions:

	UFUNCTION(BlueprintCallable, Category = "players")
		void spawnPlayers(int32 amountOfPlayersSelected);

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void foldRound();

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void betRaise(int32 amountToBet);

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void checkRound();

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void getCurrentPlayerCards();


	void updateHUD();

	void finishTurn();

	void roundFinished();

	void debugMessage(FString s);
	
	void receiveCards();

	void callRound();






	APlayerControllerP();


};

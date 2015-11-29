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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "player")
		FString currentPlayerName;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "players")
	//	int32 amountOfPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "player")
		int32 currentPlayer=0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "round management")
		int32 potSize=0;

#pragma region card variables for HUD

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 cardColor0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 cardValue0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 cardColor1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 cardValue1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 flopCard0Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 flopCard0Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 flopCard1Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 flopCard1Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 flopCard2Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 flopCard2Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 turnColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 turnValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 riverColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "cards")
		int32 riverValue;

#pragma endregion


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

	//todo: why is this UFUNCTION? 
	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void updateHUDcards();


	void updateHUD();

	void finishTurn();

	void roundFinished();

	void debugMessage(FString s);
	
	void callRound();






	APlayerControllerP();


};

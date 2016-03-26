// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PoKeIt.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerP.h"
#include "Card.h"
#include "RoundManager.h"
#include "KI.h"
#include <vector>
#include "PlayerControllerP.generated.h"



class RoundManager;

/**
 * 
 */
UCLASS()
class POKEIT_API APlayerControllerP : public APlayerController
{
	GENERATED_BODY()

private:

	/* VARIABLES */

	bool roundHasFinished = false;

	AHUD *myAhud;
	UBlueprint* myhud;
	int smallBlind;
	int bigBlind;
	int roundsPlayed = 0;
	int amountOfPlayers;
	int amountKI;

	/* FUNCTIONS */

	void updateHUDcards();

	void checkForLeavingPlayers();

	void adjustBlinds();

	void updateHUD();

public:

	/* UPROPERTY and UFUNCTION make the variables and functions to appear in blueprints */

	/* VARIABLES */

	std::vector<MyPlayerP*> players;

	RoundManager* roundManager;
	Card* currentPlayersHand[2];

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "dealerIndex")
		int32 dealerIndex=0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "turn management")
		bool turnHasFinished = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "chips")
		int32 chips;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "chips")
		int32 currentPlayersChips=0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "player")
		FString currentPlayerName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "showing a game message on screen")
		FString gameMessage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "pot")
		int32 potSize = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "pot")
		TArray<int32> pots;

#pragma region card variables for HUD

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "cards")
		int32 flopCard0Color;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "cards")
		int32 flopCard0Value;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "cards")
		int32 flopCard1Color;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "cards")
		int32 flopCard1Value;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "cards")
		int32 flopCard2Color;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "cards")
		int32 flopCard2Value;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "cards")
		int32 turnColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "cards")
		int32 turnValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "cards")
		int32 riverColor;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "cards")
		int32 riverValue;

#pragma endregion





	/* FUNCTIONS */


	// UFunctions to be called from blueprint


	/* unreal blueprints can't handle 2d arrays, therefore:
	vector contains at:
	[0] card0 color
	[1] card0 value
	[2] card1 color
	[3] card1 value
	*/
	UFUNCTION(BlueprintCallable, Category = "players' cards")
		TArray<int32> getSpecificPlayerCardData(int32 playerIndex);

	UFUNCTION(BlueprintCallable, Category = "amount of pots active in this round")
		int32 getSpecificPotSize(int32 index);

	UFUNCTION(BlueprintCallable, Category = "amount of pots active in this round")
		int32 getAmountOfPots();

	UFUNCTION(BlueprintCallable, Category = "players")
		int32 getAmountOfPlayers();

	UFUNCTION(BlueprintCallable, Category = "players")
		FString getSpecificPlayerName(int32 index);

	UFUNCTION(BlueprintCallable, Category = "check if round is finished")
		bool isRoundFinished();
	
	UFUNCTION(BlueprintCallable, Category = "check if current player is AI")
		bool currentPlayerisAI();

	UFUNCTION(BlueprintCallable, Category = "check if a specific player is AI")
		bool isSpecificPlayerAI(int32 playerIndex);

	UFUNCTION(BlueprintCallable, Category = "players")
		void spawnPlayers(int32 amountOfHumanPlayers, int32 amountOfAIplayers);

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void foldRound();

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void betRaise(int32 amountToBet);

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void checkRound();

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void callRound();

	UFUNCTION(BlueprintCallable, Category = "playerAction")
		void allIn();

	UFUNCTION(BlueprintCallable, Category = "roundstage")
		int32 getRoundstages();

	UFUNCTION(BlueprintCallable, Category = "current player's index")
		int32 getCurrentPlayerIndex();

	UFUNCTION(BlueprintCallable, Category = "bets")
		int32 getCurrentMaxBet();

	UFUNCTION(BlueprintCallable, Category = "bets")
		int32 getCurrentPlayersBetThisRound();

	UFUNCTION(BlueprintCallable, Category = "start new round")
		void startNewRound();

	UFUNCTION(BlueprintCallable, Category = "set a game message")
		void debugMessage(FString s);

	UFUNCTION(BlueprintCallable, Category = "check for possibly left players")
		bool isPlayerNameStillInGame(FString playerName);


	void roundFinished();
	
	

	void finishTurn();


	APlayerControllerP();
	// uclasses don't need destructors
};

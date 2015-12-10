// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "MyPlayerP.h"
#include "PlayerControllerP.h"
#include "Calculator.h"

class APlayerControllerP;

/**
 * 
 */
class POKEIT_API RoundManager
{
private:

	int smallBlind;
	int bigBlind;
	int pot;
	int dealerIndex;
	int currentPlayerIndex;
	int currentMaxBet;

	int lastBet;
	
	int amountOfPlayersRemaining;
	int playersDidActions;



	int roundState;

	enum Roundstages
	{
		PREFLOP,
		FLOP,
		TURN,
		RIVER,
	};

	int deck[4][13];

	int currentSidePotIndex = 0;

	// 1st dimension: amount of (side)pots
	// 2nd dimension: indices of players, anticipating in that pot
	// pots[x][0] = the actual pot
	TArray<TArray<int>> pots;



	Card* flop[3];
	Card* turn;
	Card* river;


public:

	// must be public
	MyPlayerP* players[8];


	// functions:

	Card* getFlop(int index);
	Card* getTurn();
	Card* getRiver();

	void settingBlinds();
	void increasePot(int amount);
	void resetDeck();
	
	void addPot();

	int getRoundstages();
	int getPot();
	int getAmountOfPlayersRemaining();
	int getCurrentPlayerIndex();
	int getCurrentMaxBet();
	int getCurrentPlayersBetThisRound();

	bool controlDeck(int a, int b);
	
	void checkForCommunityCards();
	void finishTurn();

	void checkRound();
	void callRound();
	void betRaise(int amount);
	void fold();

	void roundStateSwitch();
	void roundOver();

	APlayerControllerP* playerController;

	RoundManager(MyPlayerP* playersOfThisRound[8], APlayerControllerP* pc, int amountOfPlayersRemaining, int dealerIndex, int smallBlind, int bigBlind);
	~RoundManager();

	
};

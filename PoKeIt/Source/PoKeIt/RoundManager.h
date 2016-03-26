// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PoKeIt.h"
#include "UnrealString.h"
#include "Card.h"
#include "KI.h"
#include "MyPlayerP.h"
#include "PlayerControllerP.h"
#include "Calculator.h"
#include <vector>

class APlayerControllerP;

/**
 * 
 */
class POKEIT_API RoundManager
{
private:

	int smallBlind;
	int bigBlind;
	int dealerIndex;
	int currentPlayerIndex;
	int currentMaxBet;
	int lastBet;
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

	TArray<int> pots;

	Card* flop[3];
	Card* turn;
	Card* river;


public:


	std::vector<MyPlayerP*> players;


	/* functions */

	Card* getFlop(int index);
	Card* getTurn();
	Card* getRiver();

	void isAIstarting();

	void settingBlinds();
	void increasePot(int amount);
	void resetDeck();
	bool controlDeck(int a, int b);
	void addPot();

	int getRoundstages();
	int getPot();
	int getAmountOfPots();
	int getSpecificPotSize(int index);
	int getAmountOfPlayersRemaining();
	int getCurrentPlayerIndex();
	int getCurrentMaxBet();
	int getCurrentPlayersBetThisRound();
	
	void checkForCommunityCards();
	void finishTurn();

	void checkRound();
	void callRound();
	void betRaise(int amount);
	void fold();
	void allIn();

	void roundStateSwitch();
	void roundOver();

	APlayerControllerP* playerController;

	RoundManager(std::vector<MyPlayerP*> players, APlayerControllerP* pc, int dealerIndex, int smallBlind, int bigBlind);
	~RoundManager();
};

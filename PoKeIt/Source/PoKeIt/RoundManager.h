// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "MyPlayerP.h"
#include "PlayerControllerP.h"

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

	int* deck[4][13];

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

	int getRoundstages();
	int getPot();
	int getAmountOfPlayersRemaining();

	bool controlDeck(int a, int b);
	
	void checkForCommunityCards();
	void finishTurn();

	void checkRound();
	void betRaise(int amount);
	void fold();

	void roundStateSwitch();
	void roundOver();

	APlayerControllerP* playerController;

	RoundManager(MyPlayerP* playersOfThisRound[8], APlayerControllerP* pc, int amountOfPlayersRemaining);
	~RoundManager();

	
};

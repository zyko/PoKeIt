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
public:

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

	Card* flop[3];
	Card* turn;
	Card* river;
	MyPlayerP* players[8];


	// functions:

	Card* getFlop(int index);
	Card* getTurn();
	Card* getRiver();

	void settingBlinds();
	void increasePot(int amount);
	int getPot();
	
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

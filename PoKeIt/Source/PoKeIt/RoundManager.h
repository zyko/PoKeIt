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

	Card* flop[3];
	Card turn;
	Card river;
	MyPlayerP* players[8];


	// functions:

	void settingBlinds();
	void increasePot(int amount);
	int getPot();
	void checkRound();
	void finishTurn();
	void betRaise(int amount);

	APlayerControllerP* playerController;

	RoundManager(MyPlayerP* playersOfThisRound[8], APlayerControllerP* pc);
	~RoundManager();

	
};

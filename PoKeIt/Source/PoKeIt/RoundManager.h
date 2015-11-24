// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "Card.h"
#include "MyPlayerP.h"
//#include "PlayerControllerP.h"


/**
 * 
 */
class POKEIT_API RoundManager
{
public:

	int smallBlind;
	int bigBlind;
	int pot;
	Card* flop[3];
	Card turn;
	Card river;
	int dealerIndex;
	int currentPlayerIndex;
	MyPlayerP* players[8];


	void settingBlinds();
	void increasePot(int amount);
	int getPot();
	void checkRound();
	void finishTurn();

//	APlayerControllerP* playerController;

	RoundManager(MyPlayerP* playersOfThisRound[8]);
	~RoundManager();

	
};

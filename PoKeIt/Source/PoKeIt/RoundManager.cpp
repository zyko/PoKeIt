// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "RoundManager.h"
#include <string>
#include "UnrealString.h"


RoundManager::RoundManager(MyPlayerP* playersOfThisRound[8], APlayerControllerP* pc)
{
	playerController = pc;
	for (int i = 0; i < 8; ++i)
	{
		players[i] = playersOfThisRound[i];
		//players[i]->initializeNewRound();
	}


	// missing: reset the betThisRound int from player.
	// following line doesn't work. for whatever reason:
	//for (int i = 0; i < 8; ++i){players[i]->initializeNewRound();}


	/*
	*	should be given by PlayerController.
	*	set to 0 for debugging reasons.
	*/
	dealerIndex = 0;


	currentPlayerIndex = 0;
	pot = 0;

	/*	
	 *	should be given by PlayerController.
	 *	set to 8 for debugging reasons.
	 */
	amountOfPlayersRemaining = 8;
	
	smallBlind = 250;
	bigBlind = 500;
	currentMaxBet = bigBlind;

	settingBlinds();
}

void RoundManager::settingBlinds()
{
	players[dealerIndex + 1]->decreaseChips(smallBlind);
	players[dealerIndex + 1]->increaseBetThisRound(smallBlind);
	players[dealerIndex + 2]->decreaseChips(bigBlind);
	players[dealerIndex + 2]->increaseBetThisRound(bigBlind);

	increasePot(smallBlind + bigBlind);
}

int RoundManager::getPot()
{
	return pot;
}

void RoundManager::increasePot(int amount)
{
	pot += amount;
}

void RoundManager::checkRound()
{
	if (players[currentPlayerIndex]->getBetThisRound() >= currentMaxBet)
	{
		finishTurn();
	}
	else
	{
		FString s = "not enough bet to check this round";
		playerController->debugMessage(s);
	}
}

void RoundManager::betRaise(int amount)
{
	if ( (players[currentPlayerIndex]->getBetThisRound() + amount ) >= currentMaxBet)
	{
		players[currentPlayerIndex]->decreaseChips(amount);
		players[currentPlayerIndex]->increaseBetThisRound(amount);
		pot += amount;
		finishTurn();
	}
	else
	{
		FString s = "not enough bet. betThisRound is: " + players[currentPlayerIndex]->getBetThisRound();
		//FString t = " amount is: " + amount;
		//FString u = s + t;
		playerController->debugMessage(s);
	}
}

void RoundManager::finishTurn()
{
	currentPlayerIndex = ++currentPlayerIndex % amountOfPlayersRemaining;
	playerController->finishTurn();
}

RoundManager::~RoundManager()
{
}

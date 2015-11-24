// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "RoundManager.h"


RoundManager::RoundManager(MyPlayerP* playersOfThisRound[8])
{
	for (int i = 0; i < 8; ++i)
	{
		players[i] = playersOfThisRound[i];
	}
	dealerIndex = 0;
	currentPlayerIndex = 0;
	pot = 0;
	smallBlind = 250;
	bigBlind = 500;

	settingBlinds();
}

void RoundManager::settingBlinds()
{
	players[dealerIndex+1]->decreaseChips(smallBlind);
	players[dealerIndex+2]->decreaseChips(bigBlind);

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

}

void RoundManager::finishTurn()
{
	//playerController->finishTurn();

	//playerController->finishTurn();

	//ASomeGameMode* gm = (ASomeGameMode*)GetWorld()->GetAuthGameMode();
	
}

RoundManager::~RoundManager()
{
}

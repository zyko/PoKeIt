	// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "RoundManager.h"
#include "UnrealString.h"


RoundManager::RoundManager(MyPlayerP* playersOfThisRound[8], APlayerControllerP* pc, int ampr)
{
	playerController = pc;
	amountOfPlayersRemaining = ampr;

	for (int i = 0; i < amountOfPlayersRemaining; ++i)
	{
		players[i] = playersOfThisRound[i];
		players[i]->initializeNewRound();
	}


	/*
	*	should be given by PlayerController.
	*	set to 0 for debugging reasons.
	*/
	dealerIndex = 0;


	currentPlayerIndex = 0;
	pot = 0;
	roundState = PREFLOP;
	smallBlind = 0; // 250
	bigBlind = 0;	// 500
	currentMaxBet = bigBlind;
	playersDidActions = 0;

	settingBlinds();
}

void RoundManager::roundStateSwitch()
{
	if (roundState == PREFLOP)
	{
		flop[0] = new Card(FMath::RandRange(0, 3), FMath::RandRange(0, 12));
		flop[1] = new Card(FMath::RandRange(0, 3), FMath::RandRange(0, 12));
		flop[2] = new Card(FMath::RandRange(0, 3), FMath::RandRange(0, 12));
	}
	else if (roundState == FLOP)
	{
		turn = new Card(FMath::RandRange(0, 3), FMath::RandRange(0, 12));

	}
	else if (roundState == TURN)
	{
		river = new Card(FMath::RandRange(0, 3), FMath::RandRange(0, 12));

	}
	else if (roundState == RIVER)
	{
		roundOver();
	}

	playersDidActions = 0;
	roundState++;
}

void RoundManager::checkForCommunityCards()
{
	playersDidActions++;

	if (playersDidActions >= amountOfPlayersRemaining)
	{
		bool everyPlayerOnSameBet = false;
		for (int i = 0; i < amountOfPlayersRemaining; ++i)
		{
			if (players[i]->getBetThisRound() == currentMaxBet)
			{
				everyPlayerOnSameBet = true;
			}
			else
			{
				everyPlayerOnSameBet = false;
			}
		}
		if (everyPlayerOnSameBet)
		{
			roundStateSwitch();
			FString a = "roundStateSwitch() was triggered ! ";
			playerController->debugMessage(a);
		}
	}
}

void RoundManager::roundOver()
{
	//calculateWinning();
	// destroy cards of players;
	flop[0]->~Card();
	flop[1]->~Card();
	flop[2]->~Card();
	turn->~Card();
	river->~Card();
}

void RoundManager::settingBlinds()
{
	players[dealerIndex + 1]->decreaseChips(smallBlind);
	players[dealerIndex + 1]->increaseBetThisRound(smallBlind);
	players[dealerIndex + 2]->decreaseChips(bigBlind);
	players[dealerIndex + 2]->increaseBetThisRound(bigBlind);

	increasePot(smallBlind + bigBlind);
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

void RoundManager::fold()
{
	amountOfPlayersRemaining--;

	players[currentPlayerIndex]->~MyPlayerP();

	if (amountOfPlayersRemaining > 1)
	{
		for (int i = currentPlayerIndex; i < amountOfPlayersRemaining; ++i)
		{
			players[i] = players[i + 1];
		}
		playersDidActions--;
		checkForCommunityCards();
		playerController->updateHUD();
	}
	else
	{
		roundOver();
	}

	/*
	1. reduce amountOfPlayeresRemaining--
	2. adjust array to fill the gaps
	3. destroy player's cards
	4. check if theres more than 1 available
	5. if so, keep going
	6. if not, trigger roundOver();
	*/

}

void RoundManager::finishTurn()
{
	checkForCommunityCards();
	currentPlayerIndex = ++currentPlayerIndex % amountOfPlayersRemaining;
	playerController->finishTurn();
}

Card* RoundManager::getFlop(int index)
{
	if (roundState >= FLOP)
		return flop[index];
	else return NULL;
}

Card* RoundManager::getTurn()
{
	if (roundState >= TURN)
		return turn;
	else return NULL;
}

Card* RoundManager::getRiver()
{
	if (roundState >= RIVER)
		return river;
	else return NULL;
}

int RoundManager::getRoundstages()
{
	return roundState;
}

int RoundManager::getPot()
{
	return pot;
}

int RoundManager::getAmountOfPlayersRemaining()
{
	return amountOfPlayersRemaining;
}

RoundManager::~RoundManager()
{
}

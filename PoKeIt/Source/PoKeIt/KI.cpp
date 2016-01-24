// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "KI.h"
#include <iostream>

KI::KI(int givenChips, FString nameGiven)
	: MyPlayerP(givenChips, nameGiven), ptr_roundManager(NULL), ptr_kiCalculator(NULL)
{
}

KI::~KI()
{
	delete ptr_kiCalculator;
}

void KI::updateKIInformations(RoundManager *ptr_manager)
{
	setRoundManager(ptr_manager);
	setRemainingPlayers();
	setRoundIndex();
	setCommunityCards();
	updateKICalculator();
}

void KI::setRoundManager(RoundManager *ptr_manager)
{
	ptr_roundManager = ptr_manager;
}

void KI::setRemainingPlayers()
{
	remainingPlayers = ptr_roundManager->getAmountOfPlayersRemaining();
}

void KI::setRoundIndex()
{
	currentRound = ptr_roundManager->getRoundstages();
}

void KI::setCommunityCards()
{
	switch (currentRound)
	{
		case 1:
		{
			for (int i = 0; i < currentRound + 2; ++i)
			{
				communityCards.push_back(*ptr_roundManager->getFlop(i));
			}
			break;
		}
		case 2:
		{
			communityCards.push_back(*ptr_roundManager->getTurn());
			break;
		}
		case 3:
		{
			communityCards.push_back(*ptr_roundManager->getRiver());
			break;
		}
		default:
		{
			break;
		}
	}
}

void KI::updateKICalculator()
{
	if (!ptr_kiCalculator)
	{
		ptr_kiCalculator->updateInformation(communityCards);
	}
}

// calculate odds based on my own cards and the communityCards
void KI::calculateOdds()
{
	float probability = 0;

	if(ownedCardCombinations[1].getComboOwned())
	{
		probability = percentageOpponentHigherPocketPair();
	}
}

float KI::percentageOpponentHigherPocketPair()
{
	int rankOwnedPocketPair = ownedCardCombinations[1].getComboCardPtrs()[0]->getValue();
	int cardsOfHigherRank = (14 - rankOwnedPocketPair) * 4;
	// float/int Pk

	// opponents first card (of higher value) * probability of getting the pair
	float probability = ((cardsOfHigherRank / 50) * (3 / 49)) * remainingPlayers;

	for (int i = 0; i <= remainingPlayers + 1; ++i)
	{
		// Pn berechnen und auf Pk addieren
	}

	// probability -= 

	return probability;
}

void KI::checkOwnedCombinations()
{
	if (!ptr_kiCalculator)
	{
		ptr_kiCalculator = new KICalculator(currentRound, cards[0], cards[1], communityCards);
	}

	ownedCardCombinations = ptr_kiCalculator->getVecOwnedCombinations(communityCards);
}

void KI::bluff()
{

}

int KI::makeDecision()
{
	return 3;
}

void KI::folding()
{
	ptr_roundManager->fold();
}

void KI::checking()
{
	ptr_roundManager->checkRound();
}

void KI::betting(int betAmount)
{
	ptr_roundManager->betRaise(betAmount);
}

void KI::calling()
{
	ptr_roundManager->callRound();
}

void KI::raising(int raiseAmount)
{
	ptr_roundManager->betRaise(raiseAmount);
}
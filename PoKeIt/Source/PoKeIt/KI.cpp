// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "KI.h"

KI::KI(int givenChips, FString nameGiven)
	: MyPlayerP(givenChips, nameGiven), ptr_roundManager(NULL), ptr_kiCalculator(NULL)
{
}

KI::~KI()
{
	delete ptr_kiCalculator;
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

// calculate odds based on my own cards and the communityCards
void KI::calculateOdds()
{
	float value = 0;

	/*
	if(poketPair)
	{
		value = getPercentageOpponentHigherPocketPair();
	}
	*/
}

float KI::getPercentageOfBetterCardNextRound()
{
	float value = 0;

	//Percentage Flop to Turn
	if(currentRound == 1)
	{
		
	}

	//Percentage Turn to River


	//Percentage Flop to Turn + River
	

	return value;
}

float KI::getPercentageOpponentHigherPocketPair()
{
	int rankOwnedPocketPair = cards[0]->getValue();
	float value = (((14 - rankOwnedPocketPair) * 4) / 50) * (3 / 49);

	return value;
}

int KI::returnOuts()
{
	int outs = 0;
	
	//

	return outs;
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

void KI::makeDecision()
{

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

void KI::updateKIInformations(RoundManager *ptr_manager)
{
	setRoundManager(ptr_manager);
	setRemainingPlayers();
	setRoundIndex();
	setCommunityCards();
}
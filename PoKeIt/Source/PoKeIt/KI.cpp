// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "KI.h"

KI::KI(int givenChips, FString nameGiven)
	: MyPlayerP(givenChips, nameGiven)
{
	for (int i = 0; i < 8; ++i)
	{
		ownedCardOmbinations[i] = false;
	}
}

KI::~KI()
{
}

void KI::setRemainingPlayers()
{
	remainingPlayers = roundManager->getAmountOfPlayersRemaining();
}

void KI::setRoundManager(RoundManager *manager)
{
	roundManager = manager;
}

void KI::setRoundIndex()
{
	currentRound = roundManager->getRoundstages();
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

float KI::getPercentageOfBetterCard()
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

float KI::getBinomialKoeffizient(int n, int k)
{
	return (factorial(n)) / (factorial(k) * (factorial(n - k)));
}

int KI::factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

float KI::getPercentageOpponentHigherPocketPair()
{
	int rankOwnedPP = cards[0]->getValue();
	float value = (((14 - rankOwnedPP) * 4) / 50) * (3 / 49);

	return value;
}

int KI::returnOuts()
{
	int outs = 0;
	
	return outs;
}

void KI::checkOwnedCombination()
{
	Calculator* calc = new Calculator();

	/*
	HIGHCARD,
	PAIR,
	TWOPAIR,
	TRIPS,
	STRAIGHT,
	FLUSH,
	FULLHOUSE,
	QUADS,
	STRAIGHTFLUSH,
	ROYALFLUSH
	*/
	int highestCombination = calc->qualityOfCards(cards[0], cards[1], roundManager->getFlop(0), roundManager->getFlop(1), roundManager->getFlop(2), roundManager->getTurn(), roundManager->getRiver());


	calc->~Calculator();
}

void KI::bluff()
{

}

void KI::makeDecision()
{

}

void KI::folding()
{
	roundManager->fold();
}

void KI::checking()
{
	roundManager->checkRound();
}

void KI::betting(int betAmount)
{
	roundManager->betRaise(betAmount);
}

void KI::calling()
{
	roundManager->callRound();
}

void KI::raising(int raiseAmount)
{
	roundManager->betRaise(raiseAmount);
}

void KI::updateKIInformations(RoundManager *manager)
{
	setRoundManager(manager);
	setRemainingPlayers();
}
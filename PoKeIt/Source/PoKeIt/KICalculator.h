// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "OwnedCardCombination.h"
#include <vector>
#include <algorithm>
#include <functional>


class POKEIT_API KICalculator
{
public:
	KICalculator(const int round, Card *ownedCardOne, Card *ownedCardTwo, std::vector<Card> communityCards);
	~KICalculator();

	std::vector<OwnedCardCombination> getVecOwnedCombinations(std::vector<Card> communityCards);

	int getCardOuts();

private:
	int currentRound, highestPairValue;
	bool owningPair, owningTriple, owningStraight, owningFlush, owningHighestValue;
	std::vector<Card> usableCards;
	std::vector<OwnedCardCombination> allCombinations;
	
	// functions for checking cardCombinations
	OwnedCardCombination checkForHighestCard();
	OwnedCardCombination checkForPairs();
	OwnedCardCombination checkForTriple();
	OwnedCardCombination checkForStraight();
	OwnedCardCombination checkForFlush();
	OwnedCardCombination checkForFullHouse();
	OwnedCardCombination checkForQuads();
	OwnedCardCombination checkForStraightFlush();
	OwnedCardCombination checkForRoyalFlush();

	// poker-specific functions
	int calculateCardOuts();

	// mathematical functions
	int factorial(int n);
	float getBinomialKoefficient(int n, int k);
};
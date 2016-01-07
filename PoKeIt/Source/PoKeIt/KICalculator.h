// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "OwnedCardCombination.h"
#include <vector>
#include <algorithm>
#include <functional>


class POKEIT_API KICalculator
{
private:
	int currentRound, highestPairValue;
	bool owningPair, owningTriple, owningStraight, owningFlush, owningHighestValue;
	std::vector<Card> usableCards;
	std::vector<OwnedCardCombination> allCombinations;
	
	OwnedCardCombination checkForHighestCard();
	OwnedCardCombination checkForPairs();
	OwnedCardCombination checkForTriple();
	OwnedCardCombination checkForStraight();
	OwnedCardCombination checkForFlush();
	OwnedCardCombination checkForFullHouse();
	OwnedCardCombination checkForQuads();
	OwnedCardCombination checkForStraightFlush();
	OwnedCardCombination checkForRoyalFlush();

public:
	KICalculator(const int round, Card *ownedCardOne, Card *ownedCardTwo, std::vector<Card> communityCards);
	~KICalculator();

	std::vector<OwnedCardCombination> getVecOwnedCombinations();
};
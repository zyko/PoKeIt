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

	float getProbabilityDrawingUsefulCard(int probForRound);

private:
	int currentRound, highestPairValue;
	bool owningPair, owningTriple, owningStraight, owningFlush, owningHighestValue;
	Card overcardOne, overcardTwo;
	std::vector<Card> usableCards, cardOuts;
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

	std::vector<Card> calcOvercardOuts();
	std::vector<Card> calcPairOuts();
	std::vector<Card> calcTripleOuts();
	std::vector<Card> calcFullHouseOuts();

	// poker-specific functions
	void calcfinalCardOuts();
	float calcProbabilityDrawingUsefulCard(int probForRound);

	// mathematical functions
	int factorial(int n);
	float binomialKoefficient(int n, int k);
};
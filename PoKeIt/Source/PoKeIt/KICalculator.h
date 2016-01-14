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
	void updateInformation(std::vector<Card> newCommunityCards);

	float getProbabilityDrawingUsefulCard(int probForRound);

private:
	int currentRound, highestPairValue;
	bool owningPair, owningTriple, owningStraight, owningFlush, owningHighestValue;
	Card *ptr_overcardOne, *ptr_overcardTwo;
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

	/*
	index:
	1 = first pair
	2 = second pair
	3 = triple
	*/
	std::vector<Card> calcPairsOrTripleOuts(int index);
	std::vector<Card> calcStraightOuts();
	std::vector<Card> calcFlushOuts();
	std::vector<Card> calcFullHouseOuts();

	// poker-specific functions
	void calcfinalCardOuts();
	float calcProbabilityDrawingUsefulCard(int probForRound);

	// mathematical functions
	int factorial(int n);
	float binomialKoefficient(int n, int k);
};
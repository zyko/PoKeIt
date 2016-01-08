// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "KICalculator.h"

KICalculator::KICalculator(const int round, Card *ownedCardOne, Card *ownedCardTwo, std::vector<Card> communityCards)
	: currentRound(round), highestPairValue(NULL), owningPair(false), owningTriple(false), owningStraight(false), owningFlush(false), owningHighestValue(false)
{
	usableCards.push_back(*ownedCardOne);
	usableCards.push_back(*ownedCardTwo);

	if (currentRound > 1)
	{
		for (int i = 0; i < communityCards.size(); ++i)
		{
			usableCards.push_back(communityCards[i]);
		}
	}
}

KICalculator::~KICalculator()
{
}

std::vector<OwnedCardCombination> KICalculator::getVecOwnedCombinations(std::vector<Card> communityCards)
{
	// sort cards by descending value for faster cardCombinationCheck
	std::sort(usableCards.begin(), usableCards.end(), std::greater<Card>());

	// check for highest card
	allCombinations.push_back(checkForHighestCard());

	// check for highest pair
	allCombinations.push_back(checkForPairs());

	// access branch only after FLOP
	if (currentRound > 0)
	{
		// check for second pair
		allCombinations.push_back(checkForPairs());

		// check for triple
		allCombinations.push_back(checkForTriple());
		
		// check for straight
		allCombinations.push_back(checkForStraight());

		// check for flush
		allCombinations.push_back(checkForFlush());

		// check for full house
		allCombinations.push_back(checkForFullHouse());

		// check for quads
		allCombinations.push_back(checkForQuads());

		// check for straight flush
		allCombinations.push_back(checkForStraightFlush());

		// check for royal flush
		allCombinations.push_back(checkForRoyalFlush());
	}

	return allCombinations;
}

OwnedCardCombination KICalculator::checkForHighestCard()
{
	return OwnedCardCombination(0, true, usableCards.end()->getValue(), usableCards.end()->getColor());
}

OwnedCardCombination KICalculator::checkForPairs()
{
	// check for first pair
	for (int i = 0; i < usableCards.size(); ++i)
	{
		// two identical values found
		if (usableCards[i].getValue() == usableCards[i + 1].getValue())
		{
			if (!highestPairValue)
			{
				highestPairValue = usableCards[i].getValue();
				owningPair = true;
				return OwnedCardCombination(1, true, highestPairValue);
			}
			// Skip first pair
			else if (highestPairValue != usableCards[i].getValue())
			{
				return OwnedCardCombination(2, true, usableCards[i].getValue());
			}
		}
	}

	// no pairs found
	return OwnedCardCombination(1);

	// no second pair found
	if (!highestPairValue)
	{
		return OwnedCardCombination(2);
	}
}

OwnedCardCombination KICalculator::checkForTriple()
{
	for (int i = 0; i < usableCards.size() - 1; ++i)
	{
		// three identical values found
		if (usableCards[i].getValue() == usableCards[i + 1].getValue() &&
			usableCards[i + 1].getValue() == usableCards[i + 2].getValue())
		{
			owningTriple = true;
			return OwnedCardCombination(3, true, usableCards[i].getValue());
		}
	}

	// no triple found
	return OwnedCardCombination(3);
}

OwnedCardCombination KICalculator::checkForStraight()
{
	for (int i = 0; i < currentRound; ++i)
	{
		// five ascending values found
		if (usableCards[i].getValue() == usableCards[i + 1].getValue() - 1 &&
			usableCards[i + 1].getValue() == usableCards[i + 2].getValue() - 1 &&
			usableCards[i + 2].getValue() == usableCards[i + 3].getValue() - 1 && 
			usableCards[i + 3].getValue() == usableCards[i + 4].getValue() - 1)
		{	
			if (usableCards[i].getValue() == 12)
			{
				owningHighestValue = true;
			}
			owningStraight = true;
			return OwnedCardCombination(4, true, usableCards[i].getValue());
		}
	}

	// no straight found
	return OwnedCardCombination(4);
}

OwnedCardCombination KICalculator::checkForFlush()
{
	for (int i = 0; i < currentRound; ++i)
	{
		// five identical colors found
		if (usableCards[i].getValue() == usableCards[i + 1].getColor() - 1 &&
			usableCards[i + 1].getValue() == usableCards[i + 2].getColor() - 1 &&
			usableCards[i + 2].getValue() == usableCards[i + 3].getColor() - 1 &&
			usableCards[i + 3].getValue() == usableCards[i + 4].getColor() - 1)
		{
			owningFlush = true;
			return OwnedCardCombination(5, true, NULL, usableCards[i].getColor());
		}
	}

	// no straight found
	return OwnedCardCombination(5);
}

OwnedCardCombination KICalculator::checkForFullHouse()
{
	if (owningPair && owningTriple)
	{
		return OwnedCardCombination(6, true);
	}

	// no straight found
	return OwnedCardCombination(6);
}

OwnedCardCombination KICalculator::checkForQuads()
{
	for (int i = 0; i < usableCards.size() - 1; ++i)
	{
		// four identical values found
		if (usableCards[i].getValue() == usableCards[i + 1].getValue() &&
			usableCards[i + 1].getValue() == usableCards[i + 2].getValue() &&
			usableCards[i + 2].getValue() == usableCards[i + 3].getValue())
		{
			return OwnedCardCombination(7, true, usableCards[i].getValue());
		}
	}

	// no quads found
	return OwnedCardCombination(7);
}

OwnedCardCombination KICalculator::checkForStraightFlush()
{
	if (owningStraight && owningFlush)
	{
		return OwnedCardCombination(8, true);
	}

	// no straight flush found
	return OwnedCardCombination(8);
}

OwnedCardCombination KICalculator::checkForRoyalFlush()
{
	if (owningStraight && owningFlush && owningHighestValue)
	{
		return OwnedCardCombination(9, true);
	}

	// no royal flush found
	return OwnedCardCombination(9);
}

float KICalculator::getBinomialKoeffizient(int n, int k)
{
	return (factorial(n)) / (factorial(k) * (factorial(n - k)));
}

int KICalculator::factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "KICalculator.h"

KICalculator::KICalculator(const int round, Card *ownedCardOne, Card *ownedCardTwo, std::vector<Card> communityCards)
	: currentRound(round), highestPairValue(NULL), owningPair(false), owningTriple(false), owningStraight(false), owningFlush(false), owningHighestValue(false), cardOuts(0), ptr_overcardOne(NULL), ptr_overcardTwo(NULL)
{
	usableCards.push_back(*ownedCardOne);
	usableCards.push_back(*ownedCardTwo);

	// check for first Overcard
	if (*ownedCardOne > communityCards[0] &&
		*ownedCardOne > communityCards[1] &&
		*ownedCardOne > communityCards[2])
	{
		ptr_overcardOne = ownedCardOne;
	}

	// check for second Overcard
	if (*ownedCardTwo > communityCards[0] &&
		*ownedCardTwo > communityCards[1] && 
		*ownedCardTwo > communityCards[2])
	{
		ptr_overcardTwo = ownedCardTwo;
	}

	if (currentRound > 1)
	{
		for (size_t i = 0; i < communityCards.size(); ++i)
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

void KICalculator::updateInformation(std::vector<Card> newCommunityCards)
{
	++currentRound;

	usableCards.insert(usableCards.end(), newCommunityCards.begin(), newCommunityCards.end());
	std::sort(usableCards.begin(), usableCards.end(), std::greater<Card>());
}

float KICalculator::getProbabilityDrawingUsefulCard(int probForRound)
{
	return calcProbabilityDrawingUsefulCard(probForRound);
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
				// 

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


std::vector<Card> KICalculator::calcOvercardOuts()
{
	std::vector<Card> outs;

	for (int i = 0; i < 4; ++i)
	{
		if (ptr_overcardOne->getColor() != i)
		{
			outs.push_back(Card(ptr_overcardOne->getValue(), i));
		}

		// check if second overcard available
		if (!ptr_overcardTwo && ptr_overcardTwo->getColor() != i)
		{
			outs.push_back(Card(ptr_overcardTwo->getValue(), i));
		}
	}

	return outs;
}

std::vector<Card> KICalculator::calcPairsOrTripleOuts(int index)
{
	std::vector<Card> outs;
	int comboColor = allCombinations[index].getComboColor();

	for (int i = 0; i < 4; ++i)
	{
		if (comboColor != i)
		{
			outs.push_back(Card(allCombinations[index].getComboValue(), i));
		}
	}

	return outs;
}

std::vector<Card> KICalculator::calcStraightOuts()
{
	std::vector<Card> outs;
	std::vector<bool> ownedValues = std::vector<bool>(13, false);
	int gapCounter = 0, connectedCounter = 0;

	for (size_t i = 0; i < usableCards.size(); ++i)
	{
		// owning a value in straight
		ownedValues[usableCards[i].getValue()] = true;

		// Ace is also a One in Straights
		if (usableCards[i].getValue() == 12)
		{
			ownedValues[0] = true;
		}
	}

	// Missing 4 Cards in 1st and 5th place of Straight
	for (int i = 0; i < 13; ++i)
	{
		if (i > 0 && i < 9 &&
			ownedValues[i] &&
			ownedValues[i + 1] &&
			ownedValues[i + 2] &&
			ownedValues[i + 3])
		{
			// Ace as One
			if (i == 0)
			{
				for (int j = 0; j < 4; ++j)
				{
					outs.push_back(Card(12, j));
				}
			}
			else
			{
				for (int j = 0; j < 4; ++j)
				{
					outs.push_back(Card(i - 1, j));
				}
			}

			for (int j = 0; j < 4; ++j)
			{
				outs.push_back(Card(i + 4, j));
			}
		}
		// Missing 4 Cards in 2nd place of Straight
		else if (i < 10 &&
				 ownedValues[i] &&
				 ownedValues[i + 2] &&
			 	 ownedValues[i + 3] &&
			  	 ownedValues[i + 4])
		{
			for (int j = 0; j < 4; ++j)
			{
				outs.push_back(Card(i + 1, j));
			}
		}
		// Missing 4 Cards in 3rd place of Straight
		else if (i < 10 &&
				 ownedValues[i] &&
				 ownedValues[i + 1] &&
				 ownedValues[i + 3] &&
				 ownedValues[i + 4])
		{
			for (int j = 0; j < 4; ++j)
			{
				outs.push_back(Card(i + 2, j));
			}
		}
		// Missing 4 Cards in 4th place of Straight
		else if (i < 10 &&
				 ownedValues[i] &&
				 ownedValues[i + 1] &&
				 ownedValues[i + 2] &&
				 ownedValues[i + 4])
		{
			for (int j = 0; j < 4; ++j)
			{
				outs.push_back(Card(i + 3, j));
			}
		}
	}

	return outs;
}

std::vector<Card> KICalculator::calcFlushOuts()
{
	std::vector<Card> outs;
	std::vector<std::vector<int>> seperatedValuesOfEachColor;
	int outsColor = 0;

	// looping through each color
	for (int i = 0; i < 4; ++i)
	{ 
		int cardCounter = 0;

		// find four Cards of one Color
		for (int j = 0; j < 4; ++j)
		{
			for (size_t k = 0; k < usableCards.size(); ++k)
			{
				if (usableCards[k].getColor == i)
				{
					seperatedValuesOfEachColor[i].push_back(usableCards[k].getValue());
					++cardCounter;

					// four Cards found, exit Loop
					if (cardCounter == 4)
					{
						goto loopExit;
					}
				}
			}
		}
		++outsColor;
	}

	loopExit: std::sort(seperatedValuesOfEachColor[outsColor].begin(), seperatedValuesOfEachColor[outsColor].end());
	int cardIndex = 0;

	for (int i = 0; i < 13; ++i)
	{
		if (seperatedValuesOfEachColor[outsColor][cardIndex] != i)
		{
			outs.push_back(Card(i, outsColor));
			++cardIndex;
		}
	}

	return outs;
}

std::vector<Card> KICalculator::calcFullHouseOuts()
{
	std::vector<Card> outs;

	return outs;
}

std::vector<Card> maskStraightOuts(std::vector<bool> ownedValues)
{
	std::vector<Card> outsOfStraight;

	/*
	// mask for EdgeCards missing
	std::vector<bool> maskStraightFiveMissing = { true, true, true, true, false, false, false, false, false, false, false, false, false, false };
	std::vector<bool> maskStraightAceSixMissing = { false, true, true, true, true, false, false, false, false, false, false, false, false, false };
	std::vector<bool> maskStraightTwoSevenMIssing = { false, false, true, true, true, true, false, false, false, false, false, false, false, false };
	std::vector<bool> maskStraightThreeEightMissing = { false, false, false, true, true, true, true, false, false, false, false, false, false, false };
	std::vector<bool> maskStraightFourNineMissing = { false, false, false, false, true, true, true, true, false, false, false, false, false, false };
	std::vector<bool> maskStraightFiveTenMissing = { false, false, false, false, false, true, true, true, true, false, false, false, false, false };
	std::vector<bool> maskStraightSixJackMissing = { false, false, false, false, false, false, true, true, true, true, false, false, false, false };
	std::vector<bool> maskStraightSevenQueenMissing = { false, false, false, false, false, false, false, true, true, true, true, false, false, false };
	std::vector<bool> maskStraightEightKingMissing = { false, false, false, false, false, false, false, false, true, true, true, true, false, false };
	std::vector<bool> maskStraightNineAceMissing = { false, false, false, false, false, false, false, false, false, true, true, true, true, false };

	// mask for InnerCards missing
	std::vector<bool> maskStraightFiveMissing = { true, true, true, true, false, false, false, false, false, false, false, false, false, false };
	std::vector<bool> maskStraightAceSixMissing = { false, true, true, true, true, false, false, false, false, false, false, false, false, false };
	std::vector<bool> maskStraightTwoSevenMIssing = { false, false, true, true, true, true, false, false, false, false, false, false, false, false };
	std::vector<bool> maskStraightThreeEightMissing = { false, false, false, true, true, true, true, false, false, false, false, false, false, false };
	std::vector<bool> maskStraightFourNineMissing = { false, false, false, false, true, true, true, true, false, false, false, false, false, false };
	std::vector<bool> maskStraightFiveTenMissing = { false, false, false, false, false, true, true, true, true, false, false, false, false, false };
	std::vector<bool> maskStraightSixJackMissing = { false, false, false, false, false, false, true, true, true, true, false, false, false, false };
	std::vector<bool> maskStraightSevenQueenMissing = { false, false, false, false, false, false, false, true, true, true, true, false, false, false };
	std::vector<bool> maskStraightEightKingMissing = { false, false, false, false, false, false, false, false, true, true, true, true, false, false };
	std::vector<bool> maskStraightNineAceMissing = { false, false, false, false, false, false, false, false, false, true, true, true, true, false };
	*/

	for (int i = 0; i < 13; ++i)
	{
		if (i > 0 && i < 9 &&
			ownedValues[i] &&
			ownedValues[i + 1] &&
			ownedValues[i + 2] &&
			ownedValues[i + 3])
		{
			outsOfStraight.push_back(Card());
			outsOfStraight.push_back(Card());

			return outsOfStraight;
		}
	}
}

void KICalculator::calcfinalCardOuts()
{
	
}

float KICalculator::calcProbabilityDrawingUsefulCard(int probForRound)
{
	switch (probForRound)
	{
	case 1:
	{
		//
		break;
	}
	case 2:
	{
		// from flop to turn
		return cardOuts.size() / 47;
	}
	case 3:
	{
		// from flop to turn + river
		if (currentRound == 1)
		{
			return 1 - ((47 - cardOuts.size()) / 47) * ((46 - cardOuts.size()) / 46);
		}
		// from turn to river
		else
		{
			return cardOuts.size() / 46;
		}
	}
	default:
	{
		return 0.0f;
	}
	}
}

int KICalculator::factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

float KICalculator::binomialKoefficient(int n, int k)
{
	return (factorial(n)) / (factorial(k) * (factorial(n - k)));
}
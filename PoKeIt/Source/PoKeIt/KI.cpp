// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "KI.h"

KI::KI(int givenChips, FString nameGiven)
	: MyPlayerP(givenChips, nameGiven), ptr_roundManager(NULL), ptr_kiCalculator(NULL), communityCards(std::vector<Card>())
{
}

KI::~KI()
{
	delete ptr_kiCalculator;
}

void KI::setRoundManager(RoundManager *ptr_manager)
{
	ptr_roundManager = ptr_manager;
	// updateKIInformations();
}

void KI::updateKIInformations()
{
	setRemainingPlayers();
	setRoundIndex();
	setCommunityCards();
	updateKICalculator();
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
		ptr_kiCalculator = new KICalculator(currentRound, cards[0], cards[1], communityCards);
	}
	else
	{
		ptr_kiCalculator->updateInformation(cards[0], cards[1], communityCards);
	}
}

// calculate PotOdds
float KI::getPercentagePotOdds()
{
	int currentPotValue = ptr_roundManager->getPot();
	int valueToCall = ptr_roundManager->getCurrentMaxBet();

	int potOdds = currentPotValue + valueToCall;

	return (float)valueToCall / (float)potOdds;
}

/*
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
*/

void KI::checkOwnedCombinations()
{
	ownedCardCombinations = ptr_kiCalculator->getVecOwnedCombinations();
}

void KI::bluff()
{
	ptr_roundManager->callRound();
}

void KI::makeDecision()
{
	updateKIInformations();


	int debugRound = ptr_roundManager->getRoundstages();

	switch (currentRound)
	{
	case 0:
	{
		performPreFlop();
		break;
	}
	case 1:
	{
		performFlop();
		break;
	}
	case 2:
	{
		performTurn();
		break;
	}
	case 3:
	{
		performRiver();
		break;
	}
	default:
	{
		break;
	}
	}
}

void KI::performPreFlop()
{
	if (ptr_kiCalculator->preFlopRaiseDecision())
	{
		calling();
	}
	else
	{
		folding();
	}
}

void KI::performFlop()
{
	checkOwnedCombinations();

	int highestCardComboRank = 0;

	for (int i = 0; i < 10; ++i)
	{
		if (ownedCardCombinations[i].getComboOwned())
		{
			highestCardComboRank = ownedCardCombinations[i].getComboCardRanking();
		}
	}

	if (highestCardComboRank == 2)
	{
		int moneyValue = std::rand() % 2 + 1;
		raising(ptr_roundManager->getPot() * moneyValue);
	}
	else if (highestCardComboRank > 2)
	{
		int moneyValue = std::rand() % 4 + 1;
		raising(ptr_roundManager->getPot() * moneyValue);
	}

	float oddsProb = getPercentagePotOdds();
	float outsProbFlop = ptr_kiCalculator->getProbabilityDrawingUsefulCard(3);


	// check cardOuts to the potOdds
	if (oddsProb > outsProbFlop)
	{
		float differencePotOuts = oddsProb - outsProbFlop;

		if (differencePotOuts >= 0.2f) // >= 20%
		{
			if (ptr_roundManager->getCurrentMaxBet() < this->getChips())
			{
				raising(ptr_roundManager->getCurrentMaxBet() * 2);
			}
			else
			{
				ptr_roundManager->allIn();
			}
		}
		else if (differencePotOuts < 0.2f) // < 20%
		{
			calling();
		}
	}
	else
	{
		// 50% chance to bluff
		if ((std::rand() % 100 + 1) > 50)
		{
			bluff();
		}
		else
		{
			folding();
		}
	}
}

void KI::performTurn()
{
	checkOwnedCombinations();

	int highestCardComboRank = 0;

	for (int i = 0; i < 10; ++i)
	{
		if (ownedCardCombinations[i].getComboOwned())
		{
			highestCardComboRank = ownedCardCombinations[i].getComboCardRanking();
		}
	}

	if (highestCardComboRank == 2)
	{
		int moneyValue = std::rand() % 2 + 1;

		if (ptr_roundManager->getPot() * moneyValue < this->getChips())
		{
			ptr_roundManager->allIn();
		}
		else
		{
			raising(ptr_roundManager->getPot() * moneyValue);
		}
	}
	else if (highestCardComboRank > 2)
	{
		int moneyValue = std::rand() % 4 + 1;

		if (ptr_roundManager->getPot() * moneyValue < this->getChips())
		{
			ptr_roundManager->allIn();
		}
		else
		{
			raising(ptr_roundManager->getPot() * moneyValue);
		}	
	}

	float oddsProb = getPercentagePotOdds();
	float outsProbFlop = ptr_kiCalculator->getProbabilityDrawingUsefulCard(2);


	// check cardOuts to the potOdds
	if (oddsProb > outsProbFlop)
	{
		float differencePotOuts = oddsProb - outsProbFlop;

		if (differencePotOuts >= 0.2f) // >= 20%
		{
			if (ptr_roundManager->getCurrentMaxBet() < this->getChips())
			{
				raising(ptr_roundManager->getCurrentMaxBet() * 2);
			}
			else
			{
				ptr_roundManager->allIn();
			}
		}
		else if (differencePotOuts < 0.2f) // < 20%
		{
			calling();
		}
	}
	// 30% chance to bluff
	if ((std::rand() % 100 + 1) > 30)
	{
		bluff();
	}
	else
	{
		folding();
	}
}

void KI::performRiver()
{
	checkOwnedCombinations();

	int highestCardComboRank = 0;

	for (int i = 0; i < 10; ++i)
	{
		if (ownedCardCombinations[i].getComboOwned())
		{
			highestCardComboRank = ownedCardCombinations[i].getComboCardRanking();
		}
	}

	if (highestCardComboRank > 3)
	{
		int moneyValue = std::rand() % 4 + 1;

		if (ptr_roundManager->getPot() * moneyValue > this->getChips())
		{
			raising(ptr_roundManager->getPot() * moneyValue);
		}
	}

	// bluff? 30%
	if ((std::rand() % 100 + 1) > 30)
	{
		bluff();
	}
	else
	{
		folding();
	}
}

void KI::folding()
{
	//sleepDuration();
	ptr_roundManager->fold();
}

void KI::checking()
{
	//sleepDuration();
	ptr_roundManager->checkRound();
}

void KI::betting(int betAmount)
{
	//sleepDuration();
	ptr_roundManager->betRaise(betAmount);
}

void KI::calling()
{
	//sleepDuration();
	ptr_roundManager->callRound();
}

void KI::raising(int raiseAmount)
{
	//sleepDuration();
	ptr_roundManager->betRaise(raiseAmount);
}

void KI::sleepDuration()
{
	// 10 sec
	Sleep(10);
}
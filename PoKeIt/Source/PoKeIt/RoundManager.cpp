	// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "RoundManager.h"
#include "UnrealString.h"


RoundManager::RoundManager(MyPlayerP* playersOfThisRound[8], APlayerControllerP* pc, int amountOfPlayersRemaining, int dealerIndex, int smallBlind, int bigBlind)
{
	playerController = pc;
	this->amountOfPlayersRemaining = amountOfPlayersRemaining;
	
	resetDeck();

	for (int i = 0; i < amountOfPlayersRemaining; ++i)
	{
		players[i] = playersOfThisRound[i];

		int card0[2] = { FMath::RandRange(0, 3), FMath::RandRange(0, 12) };
		int card1[2] = { FMath::RandRange(0, 3), FMath::RandRange(0, 12) };		

		while (!controlDeck(card0[0], card0[1]))
		{
			card0[0] = FMath::RandRange(0, 3);
			card0[1] = FMath::RandRange(0, 12);
		}

		while (!controlDeck(card1[0], card1[1]))
		{
			card1[0] = FMath::RandRange(0, 3);
			card1[1] = FMath::RandRange(0, 12);
		}

		players[i]->initializeNewRound(card0[0], card0[1], card1[0], card1[1]);
	}


	this->dealerIndex = dealerIndex;
	currentPlayerIndex = (dealerIndex + 3 ) % amountOfPlayersRemaining;
	pot = 0;
	lastBet = bigBlind;
	roundState = PREFLOP;
	this->smallBlind = smallBlind;
	this->bigBlind = bigBlind;
	currentMaxBet = bigBlind;
	playersDidActions = 0;

	settingBlinds();
}

bool RoundManager::controlDeck(int color, int value)
{
	// this is only doable, because there can only be a maximum of 8 x 2 + 3 + 1 + 1 = 21 cards out of 52 within the game

	if ((deck[color][value]) == 0)
	{
		deck[color][value] = 1;

		return true;
	}
	else // if ((deck[color][value]) == 1)
	{
		return false;
	}
}

void RoundManager::resetDeck()
{
	for (int i = 0; i < 4; ++i)
		for (int n = 0; n < 13; ++n)
			deck[i][n] = 0;
}

void RoundManager::roundStateSwitch()
{
	if (roundState == PREFLOP)
	{
		currentPlayerIndex = (dealerIndex) % amountOfPlayersRemaining;

		int flop0[2] = { FMath::RandRange(0, 3), FMath::RandRange(0, 12) };
		int flop1[2] = { FMath::RandRange(0, 3), FMath::RandRange(0, 12) };
		int flop2[2] = { FMath::RandRange(0, 3), FMath::RandRange(0, 12) };

		while (!controlDeck(flop0[0], flop0[1]))
		{
			flop0[0] = FMath::RandRange(0, 3);
			flop0[1] = FMath::RandRange(0, 12);
		}

		while (!controlDeck(flop1[0], flop1[1]))
		{
			flop1[0] = FMath::RandRange(0, 3);
			flop1[1] = FMath::RandRange(0, 12);
		}

		while (!controlDeck(flop2[0], flop2[1]))
		{
			flop2[0] = FMath::RandRange(0, 3);
			flop2[1] = FMath::RandRange(0, 12);
		}

		flop[0] = new Card(flop0[0], flop0[1]);
		flop[1] = new Card(flop1[0], flop1[1]);
		flop[2] = new Card(flop2[0], flop2[1]);

	}
	else if (roundState == FLOP)
	{
		currentPlayerIndex = (dealerIndex) % amountOfPlayersRemaining;

		int turnA[2] = { FMath::RandRange(0, 3), FMath::RandRange(0, 12) };

		while (!controlDeck(turnA[0], turnA[1]))
		{
			turnA[0] = FMath::RandRange(0, 3);
			turnA[1] = FMath::RandRange(0, 12);
		}

		turn = new Card(turnA[0], turnA[1]);

	}
	else if (roundState == TURN)
	{
		currentPlayerIndex = (dealerIndex) % amountOfPlayersRemaining;

		int riverA[2] = { FMath::RandRange(0, 3), FMath::RandRange(0, 12) };

		while (!controlDeck(riverA[0], riverA[1]))
		{
			riverA[0] = FMath::RandRange(0, 3);
			riverA[1] = FMath::RandRange(0, 12);
		}

		river = new Card(riverA[0], riverA[1]);
		
	}
	else if (roundState == RIVER)
	{
		roundOver();
	}
	

	lastBet = bigBlind;
	playersDidActions = 0;
	roundState++;
}

void RoundManager::checkForCommunityCards()
{
	playersDidActions++;

	if (playersDidActions >= amountOfPlayersRemaining)
	{
		bool everyPlayerOnSameBet = false;
		for (int i = 0; i < amountOfPlayersRemaining; ++i)
		{
			if (players[i]->getBetThisRound() == currentMaxBet)
				everyPlayerOnSameBet = true;
			else
			{
				everyPlayerOnSameBet = false;
				break;
			}
		}
		if (everyPlayerOnSameBet)
			roundStateSwitch();
	}


}

void RoundManager::roundOver()
{
	// can be used for debugging calculator:
	/*
	players[0]->initializeNewRound(3, 5, 3, 6);
	players[1]->initializeNewRound(1, 1, 1, 12);

	amountOfPlayersRemaining = 2;

	flop[0] = new Card(0,4);
	flop[1] = new Card(0,2);
	flop[2] = new Card(0,3);
	turn    = new Card(0,5);
	river   = new Card(1,9);
*/
	// -- debugging

#pragma region winner calculation stuff
	if (amountOfPlayersRemaining > 1)
	{
		Calculator* calc = new Calculator();

		// debugging:
		calc->setPlayerController(playerController);

		int value = -1;
		int player = 0;

		int highestPlayerSoFar[2] = { -1, -1 };		// [0] = quality of cards, [1] player's index within players[];
		int currentPlayer[2];						// [0] = quality of cards, [1] player's index within players[];
		int comparisonKeyCardsArray[5];
		TArray<int> splitPotCandidates;

		for (int i = 0; i < amountOfPlayersRemaining; ++i)
		{
			currentPlayer[0] = calc->qualityOfCards(players[i]->getCard0(), players[i]->getCard1(), flop[0], flop[1], flop[2], turn, river);
			currentPlayer[1] = i;

			if (currentPlayer[0] > highestPlayerSoFar[0])
			{
				highestPlayerSoFar[0] = currentPlayer[0];
				highestPlayerSoFar[1] = currentPlayer[1];

				splitPotCandidates.Empty();

				for (int n = 0; n < 5; ++n)
					comparisonKeyCardsArray[n] = calc->keyCards[n]->getValue();

				// so keyCards[] will always be the current array, and comparisonKeyCards[] will always be the highest player's one
			}
			else if (currentPlayer[0] == highestPlayerSoFar[0]) // checking for possible splitPot
			{
				int splitPotCounter = 0;
				for (int n = 0; n < 5; ++n)
				{
					if (calc->keyCards[n]->getValue() > comparisonKeyCardsArray[n])
					{
						highestPlayerSoFar[0] = currentPlayer[0];
						highestPlayerSoFar[1] = currentPlayer[1];
						splitPotCandidates.Empty();
						break;
					}
					else if (calc->keyCards[n]->getValue() == comparisonKeyCardsArray[n])
					{
						splitPotCounter++;
					}
				}
				
				if (splitPotCounter == 5)
				{
					splitPotCandidates.Add(highestPlayerSoFar[1]);
					splitPotCandidates.Add(currentPlayer[1]);
				}
			}		
		}

		
#pragma region printing winner stuff

		FString winner;
		if (highestPlayerSoFar[0] == 0)
			winner = "High Card!";
		if (highestPlayerSoFar[0] == 1)
			winner = "Pair!";
		if (highestPlayerSoFar[0] == 2)
			winner = "Two Pair!";
		if (highestPlayerSoFar[0] == 3)
			winner = "Triple!";
		if (highestPlayerSoFar[0] == 4)
			winner = "Straight!";
		if (highestPlayerSoFar[0] == 5)
			winner = "Flush!";
		if (highestPlayerSoFar[0] == 6)
			winner = "Full House!";
		if (highestPlayerSoFar[0] == 7)
			winner = "Quads!";
		if (highestPlayerSoFar[0] == 8)
			winner = "Straight Flush!";

		if (splitPotCandidates.Num() > 0) // we got one split pot
		{
			playerController->debugMessage("we got one split pot!! with following players:");
			for (int i = 0; i < splitPotCandidates.Num(); ++i)
				playerController->debugMessage("" + players[splitPotCandidates[i]]->getName() + " with: " + winner);

		} else // we got one single player winning
			playerController->debugMessage("aaaaand the winner is: " + players[player]->getName() + " with: " + winner);
		
		calc->~Calculator();
#pragma endregion
	}
	else
		playerController->debugMessage("aaaaand the winner is: " + players[currentPlayerIndex]->getName() + " !");
#pragma endregion




	// todo: missing: 
	// player increasing chips
	// highlighting winning cards


	resetDeck();

	playerController->roundFinished();
}

void RoundManager::settingBlinds()
{
	players[dealerIndex + 1]->decreaseChips(smallBlind);
	players[dealerIndex + 1]->increaseBetThisRound(smallBlind);
	players[dealerIndex + 2]->decreaseChips(bigBlind);
	players[dealerIndex + 2]->increaseBetThisRound(bigBlind);

	increasePot(smallBlind + bigBlind);
}

void RoundManager::increasePot(int amount)
{
	//pots[pots.Num()][0] += amount;
	//pot = pots[pots.Num()][0]; // for debugging reasons / showing nooby interface stuff
}

void RoundManager::addPot()
{
	//pots.Add.Add(0);
}

void RoundManager::finishTurn()
{
	checkForCommunityCards();
	currentPlayerIndex = ++currentPlayerIndex % amountOfPlayersRemaining;

	if (players[currentPlayerIndex]->getChips() == 0)
	{
		int playersRemainingWithChips = 0;
		for (int i = 0; i < amountOfPlayersRemaining; ++i)
		{
			if (players[i]->getChips() != 0)
			{
				playersRemainingWithChips++;
			}
		}
		if (playersRemainingWithChips <= 1)
		{
			roundStateSwitch();
			roundStateSwitch();
			roundStateSwitch();
			roundStateSwitch();
		}
		else
		{
			finishTurn();
		}
	}
		
	if (currentPlayerIndex >= amountOfPlayersRemaining)
		currentPlayerIndex = 0;
	playerController->finishTurn();
}

// player actions:

void RoundManager::callRound()
{
	if ((players[currentPlayerIndex]->getChips()) >= (currentMaxBet - players[currentPlayerIndex]->getBetThisRound()))
		betRaise(currentMaxBet - players[currentPlayerIndex]->getBetThisRound());
	else
		playerController->debugMessage("couldnt call, because too less chips available");
}

void RoundManager::checkRound()
{
	// debug:
	//roundOver();

	if (players[currentPlayerIndex]->getBetThisRound() >= currentMaxBet)
		finishTurn();
	else
		playerController->debugMessage("not enough bet to check this round");
}

void RoundManager::betRaise(int amount)
{
	bool callingAllowed = false;
	bool bettingAllowed = false;
	bool raisingAllowed = false;

	if ((players[currentPlayerIndex]->getBetThisRound() + amount) == currentMaxBet)						// this is actually calling
	{
		callingAllowed = true;
	}
	else if (players[currentPlayerIndex]->getBetThisRound() == currentMaxBet && amount >= bigBlind)		// this is actually betting
	{
		bettingAllowed = true;
		lastBet = amount;
	}
	else if (players[currentPlayerIndex]->getBetThisRound() <= currentMaxBet
			&& players[currentPlayerIndex]->getBetThisRound() + amount >= currentMaxBet + lastBet)		// this is actually raising
	{
		raisingAllowed = true;
	}
	/*
	else if (amount == players[currentPlayerIndex]->getChips()											// creating side pot
			&& (players[currentPlayerIndex]->getBetThisRound() + amount) < currentMaxBet)
	{

	}
	*/





	//for (int i = 0; i < amountOfPlayersRemaining; ++i) // checking for side pot
	//{
	//	if (players[i]->getChips() == 0)
	//	{
	//		sidePotNecessary = true;
	//	}
	//	if (sidePotNecessary)
	//	{
	//		sidePots.Add
	//	}
	//}


	if (callingAllowed || bettingAllowed || raisingAllowed)
	{
		

		players[currentPlayerIndex]->decreaseChips(amount);
		players[currentPlayerIndex]->increaseBetThisRound(amount);
		currentMaxBet = players[currentPlayerIndex]->getBetThisRound();
		increasePot(amount);
		finishTurn();
	}
	else
	{
		FString a = "bet / raise has failed!";
		FString b = "in case of betting, you have to bet at least the big blind amount, which is " + FString::FromInt(bigBlind)
			+ " for the moment!";
		FString c = "in case of raising, you have to bet at least raise the amount of the last bet, which is " + FString::FromInt(lastBet)
			+ " for the moment!";
		playerController->debugMessage(a);
		playerController->debugMessage(b);
		playerController->debugMessage(c);
	}
}

void RoundManager::fold()
{
	amountOfPlayersRemaining--;

	if (amountOfPlayersRemaining > 1)
	{
		for (int i = currentPlayerIndex; i < amountOfPlayersRemaining; ++i)
			players[i] = players[i + 1];

		playersDidActions--;
		currentPlayerIndex--;

		finishTurn();
	}
	else
		roundOver();


	/*
	1. reduce amountOfPlayeresRemaining--
	2. adjust array to fill the gaps
	3. destroy player's cards
	4. check if theres more than 1 available
	5. if so, keep going
	6. if not, trigger roundOver();
	*/

}

// Getters:

Card* RoundManager::getFlop(int index)
{
	if (roundState >= FLOP)
		return flop[index];
	else return NULL;
}

Card* RoundManager::getTurn()
{
	if (roundState >= TURN)
		return turn;
	else return NULL;
}

Card* RoundManager::getRiver()
{
	if (roundState >= RIVER)
		return river;
	else return NULL;
}

int RoundManager::getRoundstages()
{
	return roundState;
}

int RoundManager::getPot()
{
	return pot;
}

int RoundManager::getAmountOfPlayersRemaining()
{
	return amountOfPlayersRemaining;
}

int RoundManager::getCurrentPlayerIndex()
{
	return currentPlayerIndex;
}

int RoundManager::getCurrentMaxBet()
{
	return currentMaxBet;
}

int RoundManager::getCurrentPlayersBetThisRound()
{
	return players[currentPlayerIndex]->getBetThisRound();
}

RoundManager::~RoundManager()
{
	flop[0]->~Card();
	flop[0] = 0;
	flop[1]->~Card();
	flop[1] = 0;
	flop[2]->~Card();
	flop[2] = 0;
	turn->~Card();
	turn = 0;
	river->~Card();
	river = 0;
	
}

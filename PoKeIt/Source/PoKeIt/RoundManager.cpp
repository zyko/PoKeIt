	// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "RoundManager.h"



RoundManager::RoundManager(std::vector<MyPlayerP*> playersOfThisRound, APlayerControllerP* pc, int dealerIndex, int smallBlind, int bigBlind)
{
	playerController = pc;
	
	resetDeck();

	players = std::vector<MyPlayerP*>(playersOfThisRound.size());

	for (unsigned int i = 0; i < players.size(); ++i)
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
	currentPlayerIndex = (dealerIndex + 3 ) % players.size();
	

	
	pots.Empty();


	addPot();
	lastBet = bigBlind;
	roundState = PREFLOP;
	this->smallBlind = smallBlind;
	this->bigBlind = bigBlind;
	currentMaxBet = bigBlind;
	playersDidActions = 0;

	settingBlinds();

}

// player actions:
// 1st step in "casual round loop"

void RoundManager::checkRound()
{
	if (players[currentPlayerIndex]->getBetThisRound() >= currentMaxBet)
		finishTurn();
	else
		playerController->debugMessage("you haven't bet enough to check this round!\nyou need to bet " + FString::FromInt((currentMaxBet - players[currentPlayerIndex]->getBetThisRound())));
}

void RoundManager::callRound()
{
	if ((players[currentPlayerIndex]->getChips()) >= (currentMaxBet - players[currentPlayerIndex]->getBetThisRound()))
		betRaise(currentMaxBet - players[currentPlayerIndex]->getBetThisRound());
	else
		playerController->debugMessage("you can't call, because you have too less chips available!\nyou need to either go all in or fold.");
}

void RoundManager::betRaise(int amountToBet)
{
	if (players[currentPlayerIndex]->getChips() >= amountToBet)
	{
		bool callingAllowed = false;
		bool bettingAllowed = false;
		bool raisingAllowed = false;
		bool allInAllowed = false;
		bool allInWithTooLessChips = false;

		if ((players[currentPlayerIndex]->getBetThisRound() + amountToBet) == currentMaxBet)						// this is actually calling
		{
			callingAllowed = true;
		}
		else if (players[currentPlayerIndex]->getBetThisRound() == currentMaxBet && amountToBet >= bigBlind)		// this is actually betting, MIGHT be allin
		{
			bettingAllowed = true;
			lastBet = amountToBet;
		}
		else if (players[currentPlayerIndex]->getBetThisRound() <= currentMaxBet
			&& players[currentPlayerIndex]->getBetThisRound() + amountToBet >= currentMaxBet + lastBet)				// this is actually raising
		{
			raisingAllowed = true;
			lastBet = (players[currentPlayerIndex]->getBetThisRound() + amountToBet) - currentMaxBet;
		}
		else if (amountToBet == players[currentPlayerIndex]->getChips())											// allIn
		{
			allInAllowed = true;
		}



		if (callingAllowed || bettingAllowed || raisingAllowed || allInAllowed)
		{
			while (players[currentPlayerIndex]->getPotAssignment() < (pots.Num() - 1))	// player is assigned to previous pot
			{
				// check if there's any player on the same potassignment as currentPlayer
				for (MyPlayerP* p : players)
				{
					if (p->getPotAssignment() == players[currentPlayerIndex]->getPotAssignment())
					{
						
						int bettingDifference = players[currentPlayerIndex]->getBetThisRound() + amountToBet - p->getBetThisRound();

						playerController->debugMessage("bettingDifference: " + FString::FromInt(bettingDifference) + "\n");


						if (bettingDifference >= 0)		// player's about to bet more than a player before him did ( because he went allin ) or equal.
						{
							int amountToBetToCallThisPot = p->getBetThisRound() - players[currentPlayerIndex]->getBetThisRound();

							players[currentPlayerIndex]->decreaseChips(amountToBetToCallThisPot);
							players[currentPlayerIndex]->increaseBetThisRound(amountToBetToCallThisPot);

							amountToBet -= amountToBetToCallThisPot;

							pots[p->getPotAssignment()] += amountToBetToCallThisPot;

							players[currentPlayerIndex]->setPotAssignment(players[currentPlayerIndex]->getPotAssignment() + 1);	// increment pot assignment
						}
						else if (bettingDifference < 0)		// player goes allin with less chips than necessary to call
						{
							// adding new pot and relocating chips between pots
							allInWithTooLessChips = true;

							players[currentPlayerIndex]->decreaseChips(amountToBet);
							players[currentPlayerIndex]->increaseBetThisRound(amountToBet);

							int amountOfPlayersInFirstPot = 0;

							for (MyPlayerP* p : players)
								if (p->getPotAssignment() >= players[currentPlayerIndex]->getPotAssignment() + 1)
									amountOfPlayersInFirstPot++;


							int subtractFromPot = amountOfPlayersInFirstPot * amountToBet;


							pots[players[currentPlayerIndex]->getPotAssignment() + 1] -= subtractFromPot;

							pots.Insert(0, players[currentPlayerIndex]->getPotAssignment());

							pots[players[currentPlayerIndex]->getPotAssignment()] += subtractFromPot + amountToBet;

							amountToBet = 0;

						}
					}
				}
			}

			if (amountToBet > 0 && players[currentPlayerIndex]->getBetThisRound() + amountToBet < lastBet) // player goes allin with less chips than necessary to call
			{
				allInWithTooLessChips = true;

				players[currentPlayerIndex]->decreaseChips(amountToBet);
				players[currentPlayerIndex]->increaseBetThisRound(amountToBet);

				players[currentPlayerIndex]->getBetThisRound();

				int amountOfPlayersInFirstPot = 0;

				pots[pots.Num() - 1] += amountToBet;
				pots.Add(0);
				int amountToTransfer;

				for (MyPlayerP* p : players)
				{
					if (p->getPotAssignment() == players[currentPlayerIndex]->getPotAssignment() && p->getBetThisRound() > players[currentPlayerIndex]->getBetThisRound())
					{
						amountToTransfer = p->getBetThisRound() - players[currentPlayerIndex]->getBetThisRound();
						pots[pots.Num() - 2] -= amountToTransfer;
						pots[pots.Num() - 1] += amountToTransfer;

						p->setPotAssignment(p->getPotAssignment() + 1);
					}
				}
				amountToBet = 0;
			}

			// now betting with remaining amount (if some is remaining)
			if (amountToBet > 0)
			{
				if (players[currentPlayerIndex]->getBetThisRound() + amountToBet > currentMaxBet) // disable creating a new pot when calling another one's allin
				{
					// if one player went allin, other players call this and one player bets another amount, then you have to add another pot
					for (unsigned int i = 0; i < players.size(); ++i)
					{
						if (players[i]->getChips() == 0 && players[i]->getPotAssignment() == pots.Num() - 1)	// check if one is assigned to current pot but has 0 chips
						{
							addPot();
							break;
						}
					}
				}				

				players[currentPlayerIndex]->decreaseChips(amountToBet);
				players[currentPlayerIndex]->increaseBetThisRound(amountToBet);
				increasePot(amountToBet);

				if (!allInWithTooLessChips)
					currentMaxBet = players[currentPlayerIndex]->getBetThisRound();

				finishTurn();
			}
			if (amountToBet == 0)
				finishTurn();
		}
		else
		{
			playerController->debugMessage("you can't bet this amount!\n press 'help' to see the rules for betting.");
		}

	}
}

void RoundManager::fold()
{
	playerController->debugMessage("fold is called");
	if (!players[currentPlayerIndex]->isPlayer())
	{
		addFoldedAI(currentPlayerIndex);
	}

	players.erase(players.begin() + currentPlayerIndex);

	if (players.size() > 1)
	{

		playersDidActions--;
		currentPlayerIndex--;

		finishTurn();
	}
	else
	{
		currentPlayerIndex = 0;
		roundOver();

	}
}

void RoundManager::allIn()
{
	betRaise(players[currentPlayerIndex]->getChips());
}

// 2nd step in "casual round loop"
void RoundManager::finishTurn()
{
	checkForCommunityCards();
	currentPlayerIndex = ++currentPlayerIndex % players.size();


	// there's the possibility, that there are a few players available, but all went all-in (mb except for one),
	// so the round must come to an end. this if-branch checks it and triggers remaining communitycards if necessary
	int playersRemainingWithChips = 0;
	int indexOfPlayerWithChips;
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		if (players[i]->getChips() != 0)
		{
			playersRemainingWithChips++;
			indexOfPlayerWithChips = i;
		}
	}
	if (playersRemainingWithChips <= 1)
	{
		int highestAllinAmount = 0;
		for (MyPlayerP* p : players)
		{
			if (p->getChips() == 0 && p->getBetThisRound() > highestAllinAmount)
			{
				highestAllinAmount = p->getBetThisRound();
			}
		}
		if (players[indexOfPlayerWithChips]->getBetThisRound() >= highestAllinAmount)
		{
			roundStateSwitch();
			roundStateSwitch();
			roundStateSwitch();
			roundStateSwitch();
		}
		
	}


	if (currentPlayerIndex >= (signed int) players.size())
		currentPlayerIndex = 0;

	
	if (!players[currentPlayerIndex]->isPlayer())
		players[currentPlayerIndex]->makeDecision();


	playerController->finishTurn();
}

// 3rd step in "casual round loop"
void RoundManager::checkForCommunityCards()
{
	playersDidActions++;

	if (playersDidActions >= (signed int) players.size())
	{
		bool everyPlayerOnSameBet = false;
		for (unsigned int i = 0; i < players.size(); ++i)
		{
			if (players[i]->getBetThisRound() == currentMaxBet)
				everyPlayerOnSameBet = true;
			else if (players[i]->getChips() == 0)
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

// possible 4th step in "casual round loop". might be called from step 3, but not necessarily
void RoundManager::roundStateSwitch()
{
	if (roundState == PREFLOP)
	{
		currentPlayerIndex = (dealerIndex) % players.size();

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
		currentPlayerIndex = (dealerIndex) % players.size();

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
		currentPlayerIndex = (dealerIndex) % players.size();

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

// prevents from creating duplicate cards
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

// triggers winning calculation and manages winning pot(s) 
void RoundManager::roundOver()
{
	FString winningMessage;

	if (players.size() > 1)
	{
		Calculator* calc = new Calculator();
		calc->setPlayerController(playerController);

		int value = -1;
		int player = 0;

		int highestPlayerSoFar[2] = { -1, -1 };					// [0] = quality of cards, [1] player's index within players[];
		int currentPlayer[2];									// [0] = quality of cards, [1] player's index within players[];
		int comparisonKeyCardsArray[5];
		TArray<int> splitPotCandidates;

		for (int k = 0; k < pots.Num(); ++k)					// going through this procedure for each pot
		{
			for (unsigned int i = 0; i < players.size(); ++i)	// checking each player
			{
				if (players[i]->getPotAssignment() >= k)		// checking to which pot player belongs to
				{												// the player with the highest potAssignment, obviously plays for each pot available
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
			}

			#pragma region defining winner String
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
#pragma endregion

			if (splitPotCandidates.Num() > 0) // that means split pot
			{
				winningMessage = "split pot ! splitting pot with: \n";
				for (int i = 0; i < splitPotCandidates.Num(); ++i)
				{
					players[splitPotCandidates[i]]->increaseChips(pots[k] / splitPotCandidates.Num());

					winningMessage += "" + players[splitPotCandidates[i]]->getName() + " (" + winner + ")\n";
				}
			}
			else
			{
				if (pots.Num() > 1)
				{
					winningMessage += "Pot number " + FString::FromInt(k);
					winningMessage += ", containing " + FString::FromInt(pots[k]) + " chips wins " + players[highestPlayerSoFar[1]]->getName() + " with: " + winner + "\n";
				}
				else
				{
					winningMessage = " " + players[highestPlayerSoFar[1]]->getName() + " wins pot, containing " + FString::FromInt(pots[k]) + " chips " + " with: " + winner + "\n";
				}

				players[highestPlayerSoFar[1]]->increaseChips(pots[k]);
			}
		}
		calc->~Calculator();
	}
	else
	{
		winningMessage = "aaaaand the winner is: " + players[currentPlayerIndex]->getName() + " !";
		players[currentPlayerIndex]->increaseChips(pots[0]);
	}

	playerController->debugMessage(winningMessage);

	playerController->finishTurn();

	pots.Empty(); // should be redundant

	resetDeck();
	playerController->roundFinished();
	foldedAI.Empty();
}

void RoundManager::addFoldedAI(int AIplayerIndex)
{
	foldedAI.Add(AIplayerIndex);
}

// setters or similars

void RoundManager::increasePot(int amount)
{
	pots[pots.Num() - 1] += amount;
}

// add one more side pot
void RoundManager::addPot()
{
	pots.Add(0);
}

// resets deck, equal to real life shuffling
void RoundManager::resetDeck()
{
	for (int i = 0; i < 4; ++i)
		for (int n = 0; n < 13; ++n)
			deck[i][n] = 0;
}

// setting blinds for the players
void RoundManager::settingBlinds()
{
	players[(dealerIndex + 1) % players.size()]->decreaseChips(smallBlind);
	players[(dealerIndex + 1) % players.size()]->increaseBetThisRound(smallBlind);
	players[(dealerIndex + 2) % players.size()]->decreaseChips(bigBlind);
	players[(dealerIndex + 2) % players.size()]->increaseBetThisRound(bigBlind);

	increasePot(smallBlind + bigBlind);
}


// Getters:

TArray<int32> RoundManager::getFoldedAIindices()
{
	return foldedAI;
}

int RoundManager::getAmountOfPots()
{
	return pots.Num();
}

int RoundManager::getSpecificPotSize(int index)
{
	if (index >= pots.Num())
		return -1;
	else
		return pots[index];
}

void RoundManager::isAIstarting()
{
	if (!players[currentPlayerIndex]->isPlayer())
		players[currentPlayerIndex]->makeDecision();
}

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
	return pots[pots.Num() - 1];
}

int RoundManager::getAmountOfPlayersRemaining()
{
	return players.size();
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

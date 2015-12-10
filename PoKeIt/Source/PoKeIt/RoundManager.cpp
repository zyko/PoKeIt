	// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "RoundManager.h"
#include "UnrealString.h"


RoundManager::RoundManager(MyPlayerP* playersOfThisRound[8], APlayerControllerP* pc, int amountOfPlayersRemaining, int dealerIndex)
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
	roundState = PREFLOP;
	smallBlind = 0; // 250
	bigBlind = 0;	// 500
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
	// can be used for debugging:


	Calculator* calc = new Calculator();
	calc->setPlayerController(playerController);

	//Card* a = new Card(3, 5);
	//Card* b = new Card(2, 4);
	//Card* c = new Card(1, 11);
	//Card* d = new Card(0, 8);
	//Card* e = new Card(3, 6);
	//Card* f = new Card(2, 7);
	//Card* g = new Card(1, 10);

	Card* a = new Card(0, 2);
	Card* b = new Card(0, 12);
	Card* c = new Card(1, 8);
	Card* d = new Card(0, 4);
	Card* e = new Card(0, 1);
	Card* f = new Card(0, 0);
	Card* g = new Card(0, 3);

	Card* h = new Card(0, 7);
	Card* i = new Card(0, 6);
	Card* j = new Card(1, 1);
	Card* k = new Card(2, 1);
	Card* l = new Card(0, 8);
	Card* m = new Card(0, 9);
	Card* n = new Card(0, 10);



	int first = calc->qualityOfCards(a, b, c, d, e, f, g);
		
	int blabla = calc->keyCards[0]->getValue();


	for (int i = 0; i < amountOfPlayersRemaining; ++i)
	{

	}


	for (int i = 0; i < 5; ++i)
	{
		playerController->debugMessage("keyCards[" + FString::FromInt(i) + "]: " + FString::FromInt(calc->keyCards[i]->getValue()));
		//test1++;
	}

	Card* test1;

	test1 = calc->getKeyCard(0);

	for (int i = 0; i < 5; ++i)
	{
		playerController->debugMessage("keyCards[" + FString::FromInt(i) + "]: " + FString::FromInt(test1->getValue()));
		test1++;
	}
		
	
	//int second = calc->qualityOfCards(h, i, j, k, l, m, n);

	/*if (first == second)
	{
	}*/


	/*keyValue1 = calc->getKeyValue();
	getKeyCard*/

	playerController->debugMessage("quality calculated: " + FString::FromInt(first));
	a->~Card();
	b->~Card();
	c->~Card();
	d->~Card();
	e->~Card();
	f->~Card();
	g->~Card();

	
	/*a = new Card(3, 8);
	b = new Card(1, 8);
	c = new Card(0, 11);
	d = new Card(0, 1);
	e = new Card(0, 0);
	f = new Card(1, 11);
	g = new Card(0, 9);

	q = calc->qualityOfCards(a, b, c, d, e, f, g);
	keyValue2 = calc->getKeyValue();

	playerController->debugMessage("quality calculated: " + FString::FromInt(q));
	playerController->debugMessage("keyValue2 is: " + FString::FromInt(keyValue2));

	a->~Card();
	b->~Card();
	c->~Card();
	d->~Card();
	e->~Card();
	f->~Card();
	g->~Card();*/


	calc->~Calculator();
	


	 //correct one:

	if (amountOfPlayersRemaining > 1)
	{
		
		Calculator* calc = new Calculator();
		calc->setPlayerController(playerController);
		int value = -1;
		int player = 0;

		for (int i = 0; i < amountOfPlayersRemaining; ++i)
		{
			int tmp = calc->qualityOfCards(players[i]->getCard0(), players[i]->getCard1(), flop[0], flop[1], flop[2], turn, river);
			if (tmp > value)
			{
				value = tmp;
				player = i;
			}
			if (tmp == value)
			{
				// todo:
			}
		}

		FString winner;

		if (value == 0)
			winner = "High Card!";
		if (value == 1)
			winner = "Pair!";
		if (value == 2)
			winner = "Two Pair!";
		if (value == 3)
			winner = "Triple!";
		if (value == 4)
			winner = "Straight!";
		if (value == 5)
			winner = "Flush!";
		if (value == 6)
			winner = "Full House!";
		if (value == 7)
			winner = "Quads!";
		if (value == 8)
			winner = "Straight Flush!";

		playerController->debugMessage("aaaaand the winner is: " + players[player]->getName() + " with: " + winner);
		
		calc->~Calculator();
		

	}
	else
		playerController->debugMessage("aaaaand the winner is: " + players[currentPlayerIndex]->getName() + " !");
	
	

	// todo: missing: 
	// player increasing chips


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
	pot += amount;
}

void RoundManager::finishTurn()
{
	checkForCommunityCards();
	currentPlayerIndex = ++currentPlayerIndex % amountOfPlayersRemaining;
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

	roundOver();


	if (players[currentPlayerIndex]->getBetThisRound() >= currentMaxBet)
		finishTurn();
	else
		playerController->debugMessage("not enough bet to check this round");
}

void RoundManager::betRaise(int amount)
{
	if ( (players[currentPlayerIndex]->getBetThisRound() + amount ) >= currentMaxBet)
	{
		players[currentPlayerIndex]->decreaseChips(amount);
		players[currentPlayerIndex]->increaseBetThisRound(amount);
		currentMaxBet = players[currentPlayerIndex]->getBetThisRound();
		pot += amount;
		finishTurn();
	}
	else
	{
		FString s = "not enough bet. betThisRound is: " + FString::FromInt(players[currentPlayerIndex]->getBetThisRound());
		playerController->debugMessage(s);
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

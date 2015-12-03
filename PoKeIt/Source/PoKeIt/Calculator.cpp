// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "Calculator.h"

Calculator::Calculator()
{
}

int Calculator::qualityOfCards(Card* hand1, Card* hand2, Card* flop0, Card* flop1, Card* flop2, Card* turn, Card* river)
{
	cards[0] = hand1;
	cards[1] = hand2;
	cards[2] = flop0;
	cards[3] = flop1;
	cards[4] = flop2;
	cards[5] = turn;
	cards[6] = river;

	/*	HIGHCARD,
		PAIR,
		TWOPAIR,
		TRIPS,
		STRAIGHT,
		FLUSH,
		FULLHOUSE,
		QUADS,
		STRAIGHTFLUSH,
		ROYALFLUSH		*/

	bubbleSortByValue();

	//debugging:
	for (int i = 0; i < amountOfCards; ++i)
		playerController->debugMessage("cards[" + FString::FromInt(i) + "]: " + FString::FromInt(cards[i]->getValue()));

	int returnValue = HIGHCARD;
	if (pairCheck(-1) >= 0)
	{
		returnValue = PAIR;
		if (pairCheck(pairCheck(-1)) >= 0)
			return TWOPAIR;
	}		
	if (tripsCheck(-1))
		returnValue = TRIPS;
	if (straightCheck(-1))
		returnValue = STRAIGHT;
	if (flushCheck() >= 0)
		returnValue = FLUSH;
	if (pairCheck(-1) != -1 && tripsCheck(pairCheck(-1)))
		returnValue = FULLHOUSE;
	if (quadsCheck())
		returnValue = QUADS;
	if (flushCheck() >= 0 && straightCheck(flushCheck()))
		returnValue = STRAIGHTFLUSH;

	/* todo:
	ROYALFLUSH ?!
	*/
	
	return returnValue;

}

// actually debugging stuff
void Calculator::setPlayerController(APlayerControllerP* pc)
{
	this->playerController = pc;
}

bool Calculator::straightCheck(int straightFlushCheck)
{
	if (straightFlushCheck == -1)
	{
		int counter = 0;

		for (int i = 0; i < amountOfCards; ++i)
		{
			if (cards[i]->getValue() + 1 == cards[i + 1]->getValue())
				counter++;
			else
				counter = 0;
			if (counter == 4)
				return true;
		}
	}
	if (straightFlushCheck == -1) // if branch for straight starting with ace only
	{
		int counter = 0;

		if (cards[amountOfCards-1]->getValue() == 12 && cards[0]->getValue() == 0)
			counter++;

		for (int i = 0; i < amountOfCards; ++i)
		{
			if ((cards[i]->getValue() + 1) == cards[i + 1]->getValue())
				counter++;
			else
				counter = 0;
			if (counter == 4)
				return true;
		}
	}
	else if (straightFlushCheck >= 0)
	{
		int counter = 0;

		for (int i = 0; i < amountOfCards; ++i)
		{
			if (cards[i]->getValue() + 1 == cards[i + 1]->getValue())
				if (cards[i]->getColor() == straightFlushCheck)
					counter++;
			else
				counter = 0;
			if (counter == 4)
				return true;
		}
	}

	return false;
}

int Calculator::flushCheck()
{
	int counter = 0;
	
	int colorReference = cards[0]->getColor();

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getColor() == colorReference)
			counter++;
		if (counter == 5)
			return colorReference;
	}

	counter = 0;

	colorReference = cards[1]->getColor();

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getColor() == colorReference)
			counter++;
		if (counter == 5)
			return colorReference;
	}

	counter = 0;

	colorReference = cards[2]->getColor();

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getColor() == colorReference)
			counter++;
		if (counter == 5)
			return colorReference;
	}


	return -1;

}

int Calculator::pairCheck(int pairCheckValue)
{
	if (pairCheckValue == -1)
	{
		if (cards[0]->getValue() == cards[1]->getValue())
			return cards[0]->getValue();
		if (cards[1]->getValue() == cards[2]->getValue())
			return cards[1]->getValue();
		if (cards[2]->getValue() == cards[3]->getValue())
			return cards[2]->getValue();
		if (cards[3]->getValue() == cards[4]->getValue())
			return cards[3]->getValue();
		if (cards[4]->getValue() == cards[5]->getValue())
			return cards[4]->getValue();
		if (cards[5]->getValue() == cards[6]->getValue())
			return cards[5]->getValue();
	}
	else if (pairCheckValue >= 0)
	{
		if (cards[0]->getValue() == cards[1]->getValue() && cards[0]->getValue() != pairCheckValue)
			return cards[0]->getValue();
		if (cards[1]->getValue() == cards[2]->getValue() && cards[1]->getValue() != pairCheckValue)
			return cards[1]->getValue();
		if (cards[2]->getValue() == cards[3]->getValue() && cards[2]->getValue() != pairCheckValue)
			return cards[2]->getValue();
		if (cards[3]->getValue() == cards[4]->getValue() && cards[3]->getValue() != pairCheckValue)
			return cards[3]->getValue();
		if (cards[4]->getValue() == cards[5]->getValue() && cards[4]->getValue() != pairCheckValue)
			return cards[4]->getValue();
		if (cards[5]->getValue() == cards[6]->getValue() && cards[5]->getValue() != pairCheckValue)
			return cards[5]->getValue();
	}
	return -1;

}

bool Calculator::tripsCheck(int pairCheckValue)
{
	if (pairCheckValue == -1)
	{
		int counter = 0;

		for (int i = 0; i < amountOfCards; ++i)
		{
			if (cards[i]->getValue() == cards[i + 1]->getValue())
				counter++;
			else
				counter = 0;
			if (counter == 2)
				return true;
		}
	}

	if (pairCheckValue >= 0)
	{
		int counter = 0;

		for (int i = 0; i < amountOfCards; ++i)
		{
			if ((cards[i]->getValue() == cards[i + 1]->getValue()) && cards[i]->getValue() != pairCheckValue)
				counter++;
			else
				counter = 0;
			if (counter == 2)
				return true;
		}
	}
	
	return false;
}

bool Calculator::quadsCheck()
{
	int counter = 0;

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getValue() == cards[i + 1]->getValue())
			counter++;
		else
			counter = 0;
		if (counter == 3)
			return true;
	}
	return false;
}

void Calculator::bubbleSortByValue()
{
	Card* tmp = cards[0];

	bool unsorted = true;

	while (unsorted)
	{
		unsorted = false;
		for (int i = 0; i < amountOfCards-1; ++i)
		{
			if (cards[i]->getValue() > cards[i + 1]->getValue())
			{
				tmp = cards[i];
				cards[i] = cards[i + 1];
				cards[i + 1] = tmp;
				unsorted = true;
			}
		}
	}
	
	/* implementation by "hand":

	if (array[0]->getValue() > array[1]->getValue())
	{
		tmp = array[0];
		array[0] = array[1];
		array[1] = tmp;
	}
	if (array[1]->getValue() > array[2]->getValue())
	{
		tmp = array[1];
		array[1] = array[2];
		array[2] = tmp;

	}
	if (array[2]->getValue() > array[3]->getValue())
	{
		tmp = array[2];
		array[2] = array[3];
		array[3] = tmp;
	}
	if (array[3]->getValue() > array[4]->getValue())
	{
		tmp = array[3];
		array[3] = array[4];
		array[4] = tmp;
	}
	if (array[4]->getValue() > array[5]->getValue())
	{
		tmp = array[4];
		array[4] = array[5];
		array[5] = tmp;
	}
	if (array[5]->getValue() > array[6]->getValue())
	{
		tmp = array[5];
		array[5] = array[6];
		array[6] = tmp;
	}
	*/

}

void Calculator::bubbleSortByColor()
{
	int n = amountOfCards - 2;
	// that means : 7 => 5
	//				6 => 4
	//				5 => 3

	Card* tmp = cards[0];

	// 7 cards, means n starts with 5:
	while (n >= 0)
	{
		for (int i = 0; i <= n; ++i)
		{
			if (cards[i]->getColor() > cards[i + 1]->getColor())
			{
				tmp = cards[i];
				cards[i] = cards[i + 1];
				cards[i + 1] = tmp;
			}
		}
		--n;
	}
}

Calculator::~Calculator()
{
	for (int i = 0; i < amountOfCards; ++i)
		cards[i]->~Card();
}

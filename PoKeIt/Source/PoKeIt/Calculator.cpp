// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "Calculator.h"

Calculator::Calculator(Card* hand1, Card* hand2, Card* flop0, Card* flop1, Card* flop2, Card* turn, Card* river)
{
	cards[0] = hand1;
	cards[1] = hand2;
	cards[2] = flop0;
	cards[3] = flop1;
	cards[4] = flop2;
	cards[5] = turn;
	cards[6] = river;
}

int Calculator::qualityOfCards()
{
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

	int returnValue = 0;

	bubbleSortByValue();

	
	if (pairCheck())
		returnValue = PAIR;
	if (tripsCheck())
		returnValue = TRIPS;
	if (quadsCheck())
		returnValue = QUADS;
	/*
	if (straightCheck())
		returnValue = STRAIGHT;
	if (flushCheck())
		returnValue = FLUSH;
	if (flushCheck() && straightCheck())
		returnValue = STRAIGHTFLUSH;
	else returnValue = HIGHCARD;
	*/
	
	return returnValue;

}

bool Calculator::straightCheck()
{
	int counter = 0;

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getValue() == cards[i + 1]->getValue() + 1)
			counter++;
		if (counter == 5)
			return true;
	}

	return false;
}

bool Calculator::flushCheck()
{
	int colorReference = 0;
	int counter = 0;
	
	colorReference = cards[0]->getColor();

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getColor() == colorReference)
			counter++;
		if (counter == 5)
			return true;
	}

	colorReference = cards[1]->getColor();

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getColor() == colorReference)
			counter++;
		if (counter == 5)
			return true;
	}

	colorReference = cards[2]->getColor();

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getColor() == colorReference)
			counter++;
		if (counter == 5)
			return true;
	}


	return false;

}

/*
int Calculator::pairCheckFake(Card* array[5])
{
	// need cards[] to be sorted by value:
	// checking for highest amount of available cards with same value
	// f. e. : if pair and trips exist, we will find trips only.

	int counter = 0;

	if (cards[0]->getValue() == cards[1]->getValue())
		counter++;
	else counter = 0;
	if (cards[1]->getValue() == cards[2]->getValue())
		counter++;
	else counter = 0;
	if (cards[2]->getValue() == cards[3]->getValue())
		counter++;
	else counter = 0;
	if (cards[3]->getValue() == cards[4]->getValue())
		counter++;
	else counter = 0;
	if (cards[4]->getValue() == cards[5]->getValue())
		counter++;
	else counter = 0;
	if (cards[5]->getValue() == cards[6]->getValue())
		counter++;
	else counter = 0;

	if (counter == 2)
		return PAIR;
	if (counter == 3)
		return TRIPS;
	if (counter == 4)
		return QUADS;
	else
		return -1;

	/* done before:
	if (array[0]->getValue() == array[1]->getValue())
		counter++;
	if (array[0]->getValue() == array[2]->getValue())
		counter++;
	if (array[0]->getValue() == array[3]->getValue())
		counter++;
	if (array[0]->getValue() == array[4]->getValue())
		counter++;
	if (array[1]->getValue() == array[2]->getValue())
		counter++;
	if (array[1]->getValue() == array[3]->getValue())
		counter++;
	if (array[1]->getValue() == array[4]->getValue())
		counter++;
	if (array[2]->getValue() == array[3]->getValue())
		counter++;
	if (array[2]->getValue() == array[4]->getValue())
		counter++;
	if (array[3]->getValue() == array[4]->getValue())
		counter++;

	if (counter == 2)
		return PAIR;
	if (counter == 3)
		return TRIPS;
	if (counter == 4)
		return QUADS;
	else
		return -1;
	
}
*/

bool Calculator::pairCheck()
{

	if (cards[0]->getValue() == cards[1]->getValue())
		return true;
	if (cards[1]->getValue() == cards[2]->getValue())
		return true;
	if (cards[2]->getValue() == cards[3]->getValue())
		return true;
	if (cards[3]->getValue() == cards[4]->getValue())
		return true;
	if (cards[4]->getValue() == cards[5]->getValue())
		return true;
	if (cards[5]->getValue() == cards[6]->getValue())
		return true;
	else
		return false;

}

bool Calculator::tripsCheck()
{
	int counter = 0;

	for (int i = 0; i < 6; ++i)
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

bool Calculator::quadsCheck()
{
	int counter = 0;

	for (int i = 0; i < 6; ++i)
	{
		if (cards[i]->getValue() == cards[i + 1]->getValue())
			counter++;
		else
			counter = 0;
		if (counter == 4)
			return true;
	}
	return false;
}

/*
void Calculator::sortCards()
{
	// Bubblesort
	Card* array[7];
	Card* tmp;

	
	int counter = 0;


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

	// 2nd round:
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

	// 3rd round:
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

	// 4th round:
	if (array[0]->getValue() > array[1]->getValue())
	{
		tmp = array[0];
		array[0] = array[1];
		array[1] = tmp;
	}

	else if (array[0]->getValue() == array[1]->getValue())
	{
		counter++;
	}
	

}
*/

void Calculator::bubbleSortByValue()
{
	// amountOfCards = 7
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
			if (cards[i]->getValue() > cards[i + 1]->getValue())
			{
				tmp = cards[i];
				cards[i] = cards[i + 1];
				cards[i + 1] = tmp;
			}
		}
		--n;
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
}

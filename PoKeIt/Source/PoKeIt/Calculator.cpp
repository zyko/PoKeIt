// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "Calculator.h"

Calculator::Calculator()
{
}

int Calculator::calculateWinning(Card* hand1, Card* hand2, Card* flop[3], Card* turn, Card* river)
{
	Card* possibleCards[8] = { hand1, hand2, flop[0], flop[1], flop[2], turn, river };


	return 1;
}

int Calculator::qualityOfCards(Card* selection[5])
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


	// todo:
	// implement sortCards()
	// following pretends selection[5] to be sorted by value:

	int returnValue = 0;
	int flushCounter = 0;
	int pairCounter = 0;
	int tripsCounter = 0;
	int quadsCounter = 0;
	int straightCounter = 0;

	for (int i = 0; i < 5; ++i)
	{
		int colorReference = selection[0]->getColor();

		// flush
		if (selection[i]->getColor() == colorReference)
		{
			flushCounter++;
		}
		else // straight
		if (i < 4)
		{
			if (selection[i]->getValue() == selection[i + 1]->getValue())
			{
				straightCounter++;

			}
		}
		else if (selection[i]->getValue())
		{

		}

	}

	if (straightCounter == 4)
	{
		returnValue = STRAIGHT;
	}

	if (flushCounter == 5)
	{
		returnValue = FLUSH;
	}
	
	return returnValue;
}

int Calculator::pairCheck(Card* array[5])
{
	int counter = 0;

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

void Calculator::sortCards()
{
	// Bubblesort
	Card* array[5];
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


	/*
	else if (array[0]->getValue() == array[1]->getValue())
	{
		counter++;
	}
	*/

}

Calculator::~Calculator()
{
}

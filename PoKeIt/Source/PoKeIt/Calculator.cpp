// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "Calculator.h"

Calculator::Calculator()
{
	keyCards.Empty();
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


	int returnValue = HIGHCARD;
	if (pairCheck(-1) >= 0)
	{
		returnValue = PAIR;
		if (pairCheck(pairCheck(-1)) >= 0)
			returnValue = TWOPAIR;
	}		
	if (tripsCheck(-1) >= 0)
		returnValue = TRIPS;
	if (straightCheck(-1) >= 0)
		returnValue = STRAIGHT;
	if (flushCheck() >= 0)
		returnValue = FLUSH;
	if (pairCheck(-1) != -1 && (tripsCheck(pairCheck(-1)) >= 0))
		returnValue = FULLHOUSE;
	if (quadsCheck() >= 0)
		returnValue = QUADS;
	if (flushCheck() >= 0 && straightCheck(flushCheck()) >= 0)
		returnValue = STRAIGHTFLUSH;

	/* todo:
	ROYALFLUSH ?!
	*/
	if (returnValue == HIGHCARD)
		setKeyValue(cards[amountOfCards - 1]->getValue());

	fillKeyCards();
	
	return returnValue;

}

void Calculator::setKeyValue(int v)
{
	keyValue = v;
}

int Calculator::getKeyValue()
{
	return keyValue;
}

void Calculator::fillKeyCards()
{
	playerController->debugMessage("keyCardsNum() is: " + FString::FromInt(keyCards.Num()) + " --- (should be2)");
	int x = 0;
	for (int i = amountOfCards-1; i >= 0; --i)
	{
		bool elementAlreadyWithin = false;
		for (int n = 0; n < keyCards.Num(); ++n)
			if ( (keyCards[n]->getValue() == cards[i]->getValue() ) && ( keyCards[n]->getColor() == cards[i]->getColor() ))
				elementAlreadyWithin = true;
		if (!elementAlreadyWithin)
			if (keyCards.Num() <= 4)
			{
				keyCards.Add(cards[i]);
				playerController->debugMessage("called adding times: " + FString::FromInt(++x) + " --- (should be3)");
			}
				
	}

	printKeyCards();
}

// actually debugging stuff
void Calculator::printKeyCards()
{
	playerController->debugMessage("keyCardsNum is: " + FString::FromInt(keyCards.Num()));
	for (int i = 0; i < keyCards.Num(); ++i)
		playerController->debugMessage("keyCards[" + FString::FromInt(i) + "]: " + FString::FromInt(keyCards[i]->getValue()));

}

// actually debugging stuff
void Calculator::setPlayerController(APlayerControllerP* pc)
{
	this->playerController = pc;
}

int Calculator::straightCheck(int straightFlushCheck)
{
	int returnValue = -1;

	if (straightFlushCheck == -1)
	{
		int counter = 0;

		for (int i = 0; i < amountOfCards; ++i)
		{
			if (cards[i]->getValue() + 1 == cards[i + 1]->getValue())
				counter++;
			else
				counter = 0;
			if (counter >= 4)
				returnValue = cards[i + 1]->getValue();
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
			if (counter >= 4)
				returnValue = cards[i + 1]->getValue();
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
			if (counter >= 4)
				returnValue = cards[i + 1]->getValue();
		}
	}
	if (returnValue >= 0)
		setKeyValue(returnValue);

	return returnValue;
}

int Calculator::flushCheck()
{
	int counter = 0;
	int returnValue = -1;

	int colorReference = cards[0]->getColor();

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getColor() == colorReference)
			counter++;
		if (counter == 5)
			returnValue = cards[i]->getValue();
	}

	counter = 0;

	colorReference = cards[1]->getColor();

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getColor() == colorReference)
			counter++;
		if (counter == 5)
			returnValue = cards[i]->getValue();
	}

	counter = 0;

	colorReference = cards[2]->getColor();

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getColor() == colorReference)
			counter++;
		if (counter == 5)
			returnValue = cards[i]->getValue();
	}

	if (returnValue >= 0)
		setKeyValue(returnValue);

	return returnValue;

}

int Calculator::pairCheck(int pairCheckValue)
{
	int returnValue = -1;

	if (pairCheckValue == -1)
	{
		for (int i = 5; i >= 0; --i)
			if (cards[i]->getValue() == cards[i + 1]->getValue())
			{
				returnValue = cards[i]->getValue();
				if (keyCards.Num() < 2)
				{
					keyCards.Add(cards[i]);
					keyCards.Add(cards[i + 1]);
				}	
			}
				

		/*
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
		*/
	}
	else if (pairCheckValue >= 0)
	{
		for (int i = 5; i >= 0; --i)
			if (cards[i]->getValue() == cards[i + 1]->getValue() && cards[i]->getValue() != pairCheckValue)
			{
				returnValue = cards[i]->getValue();
				keyCards[2] = keyCards[0];
				keyCards[3] = keyCards[1];
				keyCards[0] = cards[i];
				keyCards[1] = cards[i + 1];
				playerController->debugMessage("called adding stuff 222");
			}
				

		/*
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
			*/
	}

	if (returnValue >= 0)
		setKeyValue(returnValue);

	return returnValue;
}

int Calculator::tripsCheck(int pairCheckValue)
{
	int returnValue = -1;

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
				returnValue = cards[i + 1]->getValue();
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
				returnValue = cards[i + 1]->getValue();
		}
	}

	if (returnValue >= 0)
		setKeyValue(returnValue);
	
	return returnValue;
}

int Calculator::quadsCheck()
{
	int counter = 0;
	int returnValue = -1;

	for (int i = 0; i < amountOfCards; ++i)
	{
		if (cards[i]->getValue() == cards[i + 1]->getValue())
			counter++;
		else
			counter = 0;
		if (counter == 3)
			returnValue = cards[i + 1]->getValue();
	}


	if (returnValue >= 0)
		setKeyValue(returnValue);

	return returnValue;
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

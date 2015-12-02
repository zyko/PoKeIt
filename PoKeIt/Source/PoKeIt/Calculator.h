// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "MyPlayerP.h"

/**
 * 
 */
class POKEIT_API Calculator
{

private:

	int amountOfCards = 7;

	Card* cards[5];

public:

	enum CardRanking
	{
		HIGHCARD,
		PAIR,
		TWOPAIR,
		TRIPS,
		STRAIGHT,
		FLUSH,
		FULLHOUSE,
		QUADS,
		STRAIGHTFLUSH,
		ROYALFLUSH
	};


	// functions:

	int pairCheck(Card* array[5]);


	//void sortCards();

	bool tripsCheck();
	bool quadsCheck();
	bool pairCheck();

	bool flushCheck();

	bool straightCheck();

	void bubbleSortByValue();
	void bubbleSortByColor();

	
	int qualityOfCards();

	Calculator(Card* hand1, Card* hand2, Card* flop0, Card* flop1, Card* flop2, Card* turn, Card* river);
	~Calculator();
};

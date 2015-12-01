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

	Card* sortedCards[5];
public:

	int	calculateWinning(Card* hand1, Card* hand2, Card* flop[3], Card* turn, Card* river);

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

	void sortCards();
	int qualityOfCards(Card* selection[5]);

	Calculator();
	~Calculator();
};

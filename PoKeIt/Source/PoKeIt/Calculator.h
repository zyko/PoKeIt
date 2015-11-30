// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "MyPlayerP.h"

/**
 * 
 */
class POKEIT_API Calculator
{
public:

	int	calculateWinning(MyPlayerP* players[], Card* flop, Card* turn, Card river);

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



	Calculator();
	~Calculator();
};

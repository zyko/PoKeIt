// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"

/**
 * 
 */
class POKEIT_API MyPlayerP
{
public:


	// variables:

	int betThisRound;
	int chips;
	Card* cards[2];


	// functions: 


	void increaseBetThisRound(int amount);
	void initializeNewRound();
	int getBetThisRound();

	void debugFunc();

	void fold();

	void increaseChips();
	void decreaseChips(int amount);

	void setCards();
	Card* getCard0();
	Card* getCard1();

	int getChips();


	MyPlayerP(int givenChips);
	~MyPlayerP();
};

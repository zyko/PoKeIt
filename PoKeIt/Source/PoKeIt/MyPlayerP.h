// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Card.h"
#include "UnrealString.h"

/**
 * 
 */
class POKEIT_API MyPlayerP
{
public:


	// variables:

	FString playerName;
	int betThisRound;
	int chips;
	Card* cards[2];


	// functions: 


	void increaseBetThisRound(int amount);
	void initializeNewRound();
	int getBetThisRound();

	FString getName();

	void debugFunc();

	void fold();

	void increaseChips();
	void decreaseChips(int amount);

	void setCards();
	Card* getCard0();
	Card* getCard1();

	int getChips();


	MyPlayerP(int givenChips, FString nameGiven);
	~MyPlayerP();
};

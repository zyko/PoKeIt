// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PoKeIt.h"
#include "Card.h"
#include "UnrealString.h"

/**
 * 
 */
class POKEIT_API MyPlayerP
{

private:

	/* VARIABLES */

	FString playerName;
	int betThisRound;
	int chips;

	int potAssignment;
	bool boolIsPlayer;

	

public:

	//should actually be private, but AI..
	Card* cards[2];


	/* FUNCTIONS */

	virtual void makeDecision();
	void increaseBetThisRound(int amount);
	void initializeNewRound(int a, int b, int c, int d);
	void fold();

	void increaseChips(int amount);
	void decreaseChips(int amount);


	Card* getCard0();
	Card* getCard1();
	FString getName();

	int getBetThisRound();
	int getChips();
	int getPotAssignment();
	void setPotAssignment(int i);
	bool isPlayer();

	MyPlayerP(int givenChips, FString nameGiven, bool boolIsPlayer = false);
	~MyPlayerP();
};

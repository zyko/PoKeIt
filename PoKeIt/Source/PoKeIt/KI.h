// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyPlayerP.h"
#include "RoundManager.h"
#include <vector>

/**
 * 
 */
class POKEIT_API KI : public MyPlayerP
{
private:
	// variables
	RoundManager *roundManager;
	int remainingPlayers;
	/*
	0 = PREFLOP,
	1 = FLOP,
	2 = TURN,
	3 = RIVER,
	*/
	int currentRound;

	/*
	value between 0% - 100%

	0 = high card
	1 = pair
	2 = two pairs
	3 = trips
	4 = stright
	5 = flush
	6 = full house
	7 = quads
	8 = straight flush
	9 = royal flush
	*/
	std::vector<double> odds;


	// functions
	void setRemainingPlayers();
	void setRoundManager(RoundManager *manager);
	void setRoundIndex();

	void setKIAgressive(); // are we rushin' in ...
	void setKIDefensive(); // ... or goin' sneaky peaky like?

	void calculateOdds();

	void makeDecision();

	void folding();
	void checking();
	void betting(int betAmount);
	void calling();
	void raising(int raiseAmount);

public:
	KI(int givenChips, FString nameGiven);
	~KI();

	void updateKIInformations(RoundManager *manager);
};
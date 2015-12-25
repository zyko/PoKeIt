// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "KI.h"

KI::KI(int givenChips, FString nameGiven)
	: MyPlayerP(givenChips, nameGiven)
{
}

KI::~KI()
{
}

void KI::setRemainingPlayers()
{
	remainingPlayers = roundManager->getAmountOfPlayersRemaining();
}

void KI::setRoundManager(RoundManager *manager)
{
	roundManager = manager;
}

void KI::setRoundIndex()
{
	currentRound = roundManager->getRoundstages();
}

// calculate odds based on my own cards and the communityCards
void KI::calculateOdds()
{
	
}

void KI::makeDecision()
{

}

void KI::folding()
{
	roundManager->fold();
}

void KI::checking()
{
	roundManager->checkRound();
}

void KI::betting(int betAmount)
{
	roundManager->betRaise(betAmount);
}

void KI::calling()
{
	roundManager->callRound();
}

void KI::raising(int raiseAmount)
{
	roundManager->betRaise(raiseAmount);
}

void KI::updateKIInformations(RoundManager *manager)
{
	setRoundManager(manager);
	setRemainingPlayers();
}
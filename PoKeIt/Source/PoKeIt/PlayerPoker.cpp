// Fill out your copyright notice in the Description page of Project Settings.


#include "PoKeIt.h"
#include "PlayerPoker.h"
#include "PoKeItGameMode.h"
#include "Card.h"

int chips;



/*
Card* APlayerPoker::getHand()
{
return hand*;
}
*/

// since UE 4.6, constructor is not needed anymore
APlayerPoker::APlayerPoker()
{
	chips = 1337;
	//APoKeItGameMode * p = new APoKeItGameMode();
}

void APlayerPoker::increaseChips()
{
	
	chips += 1000;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "int chips was increased by 1000");

}

void APlayerPoker::receiveCards()
{

}

void APlayerPoker::callRound()
{

}

void APlayerPoker::checkRound()
{

}

void APlayerPoker::raiseRound()
{

}

void APlayerPoker::foldRound()
{

}




// Fill out your copyright notice in the Description page of Project Settings.


#include "PoKeIt.h"
#include "PlayerPoker.h"
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
}


void APlayerPoker::anyFunc()
{
	
	chips += 1337;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "debug msg");

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




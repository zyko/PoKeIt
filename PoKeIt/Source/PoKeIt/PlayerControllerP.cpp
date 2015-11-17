// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "PlayerControllerP.h"
#include "PoKeItGameMode.h"
#include "PlayerP.h"
#include "Card.h"



/*
Card* PlayerControllerP::getHand()
{
return hand*;
}
*/

// since UE 4.6, constructor is not needed anymore
APlayerControllerP::APlayerControllerP()
{
	chips = 1337;
	//APoKeItGameMode * p = new APoKeItGameMode();
}

void APlayerControllerP::increaseChips()
{

	chips += 1000;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "int chips was increased by 1000");

}

/*
void APlayerControllerP::createPlayers(int playerNumber)
{
	for (int i = 0; i <= playerNumber; ++i)
	{
		players.get(i) = new PlayerP();
	}

}
*/

void APlayerControllerP::receiveCards()
{

}

void APlayerControllerP::callRound()
{

}

void APlayerControllerP::checkRound()
{

}

void APlayerControllerP::raiseRound()
{

}

void APlayerControllerP::foldRound()
{

}





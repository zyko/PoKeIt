// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "PlayerControllerP.h"
#include "PoKeItGameMode.h"
#include "Card.h"
#include "MyPlayerP.h"
//#include "UnrealString.h"

// todo:
int amountOfPlayers;
// default = 5

//todo:
/* gotta update player HUD from players directly
*/
// since UE 4.6, constructor is not needed anymore
APlayerControllerP::APlayerControllerP()
{
	chips = 1337;
}

void APlayerControllerP::spawnPlayers(int amountOfPlayersSelected)
{
	amountOfPlayers = amountOfPlayersSelected;

	for (int i = 0; i < amountOfPlayers; ++i)
	{
		FString nameTMP = "Player " + FString::FromInt(i);
		MyPlayerP *spawnedPlayer = new MyPlayerP(10000, nameTMP);
		spawnedPlayer->setCards();
		players[i] = spawnedPlayer;
	}

	roundManager = new RoundManager(players, this, amountOfPlayers);


	updateHUD();	
}

// still needs to be called by either winning calculation or playercontroller.
void APlayerControllerP::roundFinished()
{
	roundManager->~RoundManager();
}

void APlayerControllerP::updateHUD()
{
	currentPlayersChips = roundManager->players[currentPlayer]->getChips();
	currentPlayerName = roundManager->players[currentPlayer]->getName();
	potSize = roundManager->getPot();
	updateHUDcards();
}

void APlayerControllerP::finishTurn()
{
	currentPlayer = ++currentPlayer % roundManager->getAmountOfPlayersRemaining();
	updateHUD();
}

void APlayerControllerP::updateHUDcards()
{
	currentPlayersHand[0] = roundManager->players[currentPlayer]->getCard0();
	currentPlayersHand[1] = roundManager->players[currentPlayer]->getCard1();

	cardColor0 = currentPlayersHand[0]->getColor();
	cardValue0 = currentPlayersHand[0]->getValue();
	cardColor1 = currentPlayersHand[1]->getColor();
	cardValue1 = currentPlayersHand[1]->getValue();
	
	if (roundManager)
	{
		
		if (roundManager->getFlop(0) != NULL)
		{
			flopCard0Color = roundManager->getFlop(0)->getColor();
			flopCard0Value = roundManager->getFlop(0)->getValue();

			flopCard1Color = roundManager->getFlop(1)->getColor();
			flopCard1Value = roundManager->getFlop(1)->getValue();

			flopCard2Color = roundManager->getFlop(2)->getColor();
			flopCard2Value = roundManager->getFlop(2)->getValue();
		}
		if (roundManager->getTurn() != NULL)
		{
			turnColor = roundManager->getTurn()->getColor();
			turnValue = roundManager->getTurn()->getValue();

		}

		if (roundManager->getRiver() != NULL)
		{
			riverColor = roundManager->getRiver()->getColor();
			riverValue = roundManager->getRiver()->getValue();
		}
	}
}


void APlayerControllerP::betRaise(int atb)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("APC betRaise was called with: %i"), atb));
	roundManager->betRaise(atb);

}

void APlayerControllerP::foldRound()
{
	roundManager->fold();
}

void APlayerControllerP::callRound()
{

}

void APlayerControllerP::checkRound()
{
	roundManager->checkRound();
}

void APlayerControllerP::debugMessage(FString s)
{

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(s));


	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, s);

}




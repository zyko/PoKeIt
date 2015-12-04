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
		players[i] = spawnedPlayer;
	}

	roundManager = new RoundManager(players, this, amountOfPlayers, dealerIndex);

	/*
	KI bla = new KI(..);

	bla.setRoundManager(roundManager);
	*/

	updateHUD();	
}



// still needs to be called by either winning calculation or playercontroller.
void APlayerControllerP::roundFinished()
{
	roundManager->~RoundManager();
}

void APlayerControllerP::updateHUD()
{
	currentPlayersChips = roundManager->players[roundManager->getCurrentPlayerIndex()]->getChips();
	currentPlayerName = roundManager->players[roundManager->getCurrentPlayerIndex()]->getName();
	potSize = roundManager->getPot();
	updateHUDcards();
}

// todo: still necessary? could call updateHUD() directly
void APlayerControllerP::finishTurn()
{
	//currentPlayer = ++currentPlayer % roundManager->getAmountOfPlayersRemaining();
	updateHUD();
}

void APlayerControllerP::roundOver()
{
	//roundManager->~RoundManager();
}

void APlayerControllerP::updateHUDcards()
{
	currentPlayersHand[0] = roundManager->players[roundManager->getCurrentPlayerIndex()]->getCard0();
	currentPlayersHand[1] = roundManager->players[roundManager->getCurrentPlayerIndex()]->getCard1();

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

// player actions:

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
	roundManager->callRound();
}

void APlayerControllerP::checkRound()
{
	roundManager->checkRound();
}

// getters:

int APlayerControllerP::getRoundstages()
{
	return roundManager->getRoundstages();
}

int APlayerControllerP::getCurrentMaxBet()
{
	if (roundManager != NULL)
	{
		return roundManager->getCurrentMaxBet();
	}
	else
		return 0;
}

int APlayerControllerP::getCurrentPlayersBetThisRound()
{
	if (roundManager != NULL)
	{
		return roundManager->getCurrentPlayersBetThisRound();
	}
	else
		return 0;
	
}

void APlayerControllerP::debugMessage(FString s)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, s);
}




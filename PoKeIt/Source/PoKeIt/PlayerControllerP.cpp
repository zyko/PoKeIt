// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "PlayerControllerP.h"
#include "PoKeItGameMode.h"
#include "Card.h"
#include "MyPlayerP.h"


// since UE 4.6, constructor is not needed anymore
APlayerControllerP::APlayerControllerP()
{

}

void APlayerControllerP::setPlayerAmount(int amount)
{
	debugMessage("set Player Amount was called!!!!");
	amountOfPlayers = amount;
}

void APlayerControllerP::spawnPlayers(int amountOfHumanPlayers, int amountOfAIplayers)
{
	amountOfPlayers= amountOfHumanPlayers;
	amountKI = amountOfAIplayers;

	int startingChips = 10000;
	smallBlind = startingChips / 100;
	bigBlind = smallBlind * 2;


	#pragma region create human players
	for (int i = 0; i < amountOfPlayers; ++i)
	{
		FString nameTMP = "Player " + FString::FromInt(i);
		MyPlayerP *spawnedPlayer = new MyPlayerP(startingChips, nameTMP, true);

		players.push_back(spawnedPlayer);
	}
	#pragma endregion

	#pragma region create AI
	TArray<KI*> kitmp;
	for (int i = 0; i < amountKI; ++i)
	{
		KI *kiPlayer = new KI(startingChips, "KI " + FString::FromInt(i));
		kitmp.Add(kiPlayer);

		players.push_back(kiPlayer);

	}
	amountOfPlayers += amountKI;

	#pragma endregion


	roundManager = new RoundManager(players, this, dealerIndex, smallBlind, bigBlind);


	for (KI* ki : kitmp)
		ki->setRoundManager(roundManager);
	
	roundManager->isAIstarting();

	updateHUD();
}


void APlayerControllerP::checkForLeavingPlayers()
{
	for (int i = 0; i < players.size(); ++i)
	{
		if (players[i]->getChips() <= 0)
		{
			players.erase(players.begin() + i);
			amountOfPlayers--;
		}
	}
}

// this is triggered by HUDwidget.bp
void APlayerControllerP::startNewRound()
{
	roundHasFinished = false;
	checkForLeavingPlayers();
	roundManager->~RoundManager();
	
	roundManager = new RoundManager(players, this, dealerIndex, smallBlind, bigBlind);


	for (int i = 0; i < players.size(); ++i)
	{
		if (!players[i]->isPlayer())
		{
			KI* kiPointer = (KI*) players[i];

			kiPointer->setRoundManager(roundManager);
		}
	}

	roundManager->isAIstarting();

	updateHUD();

}

void APlayerControllerP::roundFinished()
{
	roundHasFinished = true;
	roundsPlayed++;
	adjustBlinds();
	dealerIndex++;
}

void APlayerControllerP::adjustBlinds()
{
	if ((roundsPlayed % 15) == 0)
	{
		if (roundsPlayed < 15 * 6)
		{
			smallBlind += 100;
			bigBlind = smallBlind * 2;
		}
		if (roundsPlayed < 15 * 8)
		{
			smallBlind += 200;
			bigBlind = smallBlind * 2;
		}
		if ( roundsPlayed < 15 * 10)
		{
			smallBlind += 500;
			bigBlind = smallBlind * 2;
		}
		if (roundsPlayed < 15 * 15)
		{
			smallBlind += 1000;
			bigBlind = smallBlind * 2;
		}
	}
}

void APlayerControllerP::finishTurn()
{
	turnHasFinished = true;
	updateHUD();
}

void APlayerControllerP::updateHUD()
{
	currentPlayersChips = roundManager->players[roundManager->getCurrentPlayerIndex()]->getChips();
	currentPlayerName = roundManager->players[roundManager->getCurrentPlayerIndex()]->getName();
	potSize = roundManager->getPot();
	updateHUDcards();
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

void APlayerControllerP::allIn()
{
	roundManager->allIn();
}

// getters:

FString APlayerControllerP::getSpecificPlayerName(int32 index)
{
	return roundManager->players[index]->getName();
}

int APlayerControllerP::getAmountOfPlayers()
{
	return amountOfPlayers;
}

bool APlayerControllerP::isRoundFinished()
{
	return roundHasFinished;
}

bool APlayerControllerP::currentPlayerisAI()
{
	if (!players[roundManager->getCurrentPlayerIndex()]->isPlayer())
	{
		return true;
	}
	
	return false;
}

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

int APlayerControllerP::getCurrentPlayerIndex()
{
	return roundManager->getCurrentPlayerIndex();
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


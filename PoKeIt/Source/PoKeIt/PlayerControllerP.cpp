// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "PlayerControllerP.h"
#include "PoKeItGameMode.h"
#include "PlayerP.h"
#include "Card.h"


int amountOfPlayers;
APlayerP* players[8];
//APlayerP playersTest[8];
int test[8];

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
}

void APlayerControllerP::finishTurn()
{
	currentPlayer = ++currentPlayer % amountOfPlayers;
	updateCurrentPlayersChips();
}


void APlayerControllerP::increaseChips()
{
	chips += 1000;
	players[currentPlayer]->increaseChips();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "int chips was increased by 1000");
	updateCurrentPlayersChips();
}

void APlayerControllerP::updateCurrentPlayersChips()
{
	currentPlayersChips = players[currentPlayer]->getChips();
}


void APlayerControllerP::spawnPlayers(int amountOfPlayersSelected)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "spawnPlayers was called");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("amountOfPlayersSelected is: %i"), amountOfPlayersSelected));

	amountOfPlayers = amountOfPlayersSelected;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("amountOfPlayers is: %i"), amountOfPlayers));

	/*
	UWorld* const World = GetWorld();

	if (World)
	{
		for (int i = 0; i < amountOfPlayers; ++i)
		{

			FVector position = FVector(500, 100, 30);
			FRotator rotator(0, 0, 0);

			APlayerP* spawnedPlayer = World->SpawnActor<APlayerP>(APlayerP::StaticClass(), position, rotator);

			players[i] = spawnedPlayer;

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "for loop entered");

		}
	}
	players[2]->increaseChips();
	*/
}


void APlayerControllerP::foldRound()
{
	finishTurn();
}


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


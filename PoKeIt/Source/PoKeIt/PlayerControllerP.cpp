// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "PlayerControllerP.h"
#include "PoKeItGameMode.h"
#include "PlayerP.h"
#include "Card.h"


int amountOfPlayers;
//APlayerP* players[8];


/*
Card* PlayerControllerP::getHand()
{
return hand*;
}
*/

// since UE 4.6, constructor is not needed anymore
APlayerControllerP::APlayerControllerP()
{
	amountOfPlayers = 4;
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
	spawnPlayers(amountOfPlayers);
	//players[currentPlayer]->increaseChips();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "int chips was increased by 1000");
	updateCurrentPlayersChips();
}

void APlayerControllerP::updateCurrentPlayersChips()
{
	//currentPlayersChips = players[currentPlayer]->getChips();
}


void APlayerControllerP::spawnPlayers(int amountOfPlayersSelected)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "spawnPlayers was called");
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("amountOfPlayersSelected is: %i"), amountOfPlayersSelected));

	amountOfPlayers = amountOfPlayersSelected;

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("amountOfPlayers is: %i"), amountOfPlayers));

	
	UWorld* const World = GetWorld();

	if (World)
	{

		FVector position = FVector(500, 100, 30);
		FRotator rotator(0, 0, 0);

		APlayerP* spawnedPlayer1 = World->SpawnActor<APlayerP>(APlayerP::StaticClass(), position, rotator);
		spawnedPlayer1->increaseChips();
		spawnedPlayer1->increaseChips();



		FVector position2 = FVector(300, 150, 30);
		FRotator rotator2(0, 0, 0);

		APlayerP* spawnedPlayer2 = World->SpawnActor<APlayerP>(APlayerP::StaticClass(), position2, rotator2);
		spawnedPlayer2->increaseChips();

		betRaise(spawnedPlayer1, spawnedPlayer2);
	


	/*
		for (int i = 0; i < amountOfPlayers; ++i)
		{

			FVector position = FVector(500, 100, 30);
			FRotator rotator(0, 0, 0);

			APlayerP* spawnedPlayer = World->SpawnActor<APlayerP>(APlayerP::StaticClass(), position, rotator);

			//players[i] = spawnedPlayer;

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "for loop entered");

		}
		*/
	}
	//players[2]->increaseChips();
	
}

void APlayerControllerP::betRaise(APlayerP* p1, APlayerP* p2)
{
	int chips1 = p1->getChips();
	int chips2 = p2->getChips();
	//playersChips = dummy->getChips();
	
	
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("player1s chips are: %i"), chips1));
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("player2s chips are: %i"), chips2));

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




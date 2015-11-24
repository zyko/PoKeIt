// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "MyPlayerP.h"





MyPlayerP::MyPlayerP(int givenChips)
{
	chips = givenChips;
}

void MyPlayerP::setCards()
{
	cards[0] = new Card(FMath::RandRange(0, 3), FMath::RandRange(0, 12));
	cards[1] = new Card(FMath::RandRange(0, 3), FMath::RandRange(0, 12));
}


Card* MyPlayerP::getCard0()
{
	return cards[0];
}

Card* MyPlayerP::getCard1()
{
	return cards[1];
}


void MyPlayerP::increaseChips()
{
	chips += 100;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "PlayerP's chips were increased by 100 ");
}

void MyPlayerP::decreaseChips(int amount)
{
	chips -= amount;
}


int MyPlayerP::getChips()
{
	return chips;
}

void MyPlayerP::debugFunc()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, "PlayerP's debug Func was called");
}

void MyPlayerP::fold()
{

}

MyPlayerP::~MyPlayerP()
{
}

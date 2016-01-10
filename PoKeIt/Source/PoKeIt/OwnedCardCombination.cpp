// Fill out your copyright notice in the Description page of Project Settings.

#include "PoKeIt.h"
#include "OwnedCardCombination.h"

OwnedCardCombination::OwnedCardCombination(int cardRank, bool owned, int value, int color)
	:comboCardRank(cardRank), comboOwned(owned), comboValue(value), comboColor(color)
{
}

OwnedCardCombination::~OwnedCardCombination()
{
}

void OwnedCardCombination::setComboOwned(bool owned)
{
	comboOwned = owned;
}

void OwnedCardCombination::setComboValue(int value)
{
	comboValue = value;
}

void OwnedCardCombination::setComboColor(int color)
{
	comboColor = color;
}

int OwnedCardCombination::getComboCardRanking()
{
	return comboCardRank;
}

bool OwnedCardCombination::getComboOwned()
{
	return comboOwned;
}

int OwnedCardCombination::getComboValue()
{
	return comboValue;
}

int OwnedCardCombination::getComboColor()
{
	return comboColor;
}
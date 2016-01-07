// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class POKEIT_API OwnedCardCombination
{
private:
	int comboCardRank;
	bool comboOwned;
	int comboValue;
	int comboColor;

public:
	OwnedCardCombination(int cardRank, bool owned = false, int value = NULL, int color = NULL);
	~OwnedCardCombination();

	// Setter
	void setComboOwned(bool owned);
	void setComboValue(int value);
	void setComboColor(int color);

	// Getter
	int getComboCardRanking();
	bool getComboOwned();
	int getComboValue();
	int getCmboColor();
};
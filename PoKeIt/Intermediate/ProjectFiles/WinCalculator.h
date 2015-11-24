#ifndef WINCALCULATOR_H
#define WINCALCULATOR_H

#include <vector>
#include "Card.h"

#pragma once
class WinCalculator
{
	std::vector<Card> playerCards;

public:
	WinCalculator(  std::vector<Card> communityCards,
					std::vector<Card> playerOneCards,
					std::vector<Card> playerTwoCards);

	WinCalculator(	std::vector<Card> communityCards, 
					std::vector<Card> playerOneCards,
					std::vector<Card> playerTwoCards,
					std::vector<Card> playerThreeCards);

	WinCalculator(  std::vector<Card> communityCards,
					std::vector<Card> playerOneCards,
					std::vector<Card> playerTwoCards,
					std::vector<Card> playerThreeCards,
					std::vector<Card> playerFourCards);
private:
	void checkBestCardsForPlayer(std::vector<Card> communityCards, std::vector<Card> playerCards);

	std::vector<Card> getHighCards(std::vector<Card> communityCards, std::vector<Card> playerCards);
	std::vector<Card> getOnePairCards(std::vector<Card> communityCards, std::vector<Card> playerCards);
	std::vector<Card> getTwoPairCards(std::vector<Card> communityCards, std::vector<Card> playerCards);
	std::vector<Card> getThreeOfAKindCards(std::vector<Card> communityCards, std::vector<Card> playerCards);
	std::vector<Card> getStraightCards(std::vector<Card> communityCards, std::vector<Card> playerCards);
	std::vector<Card> getFlushCards(std::vector<Card> communityCards, std::vector<Card> playerCards);
	std::vector<Card> getFullHouseCards(std::vector<Card> communityCards, std::vector<Card> playerCards);
	std::vector<Card> getFourOfAKindCards(std::vector<Card> communityCards, std::vector<Card> playerCards);
	std::vector<Card> getStraightFlushCards(std::vector<Card> communityCards, std::vector<Card> playerCards);
	std::vector<Card> getRoyalFlushCards(std::vector<Card> communityCards, std::vector<Card> playerCards);
};

#endif // !WINCALCULATOR_H
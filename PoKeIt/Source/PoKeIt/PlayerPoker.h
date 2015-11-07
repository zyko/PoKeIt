#ifndef PLAYERPOKER.H
#define PLAYERPOKER.H

class POKEIT_API PlayerPoker
{
public:
	PlayerPoker();
	~PlayerPoker();
	// Card* getHand() const;

private:
	// Card hand[2];
	int chips;

	void receiveCards();
	void callRound();
	void checkRound();
	void raiseRound();
	void foldRound();
};
#endif
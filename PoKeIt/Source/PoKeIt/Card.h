#ifndef CARD.H
#define CARD.H

class POKEIT_API Card
{
private:
	/*
	0 = pik
	1 = herz
	2 = karo
	3 = kreuz
	*/
	int color;

	/*
	0 = ass
	1 = 2
	2 = 3
	3 = 4
	4 = 5
	5 = 6
	6 = 7
	7 = 8
	8 = 9
	9 = 10
	10 = bube
	11 = dame
	12 = koenig
	*/
	int value;

public:
	Card();
	Card(const int, const int);
	~Card();
};
#endif

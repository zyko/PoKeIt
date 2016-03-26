#include "PoKeIt.h"
#include "Card.h"


Card::Card()
{
	
}

Card::Card(const int color, const int value)
	:color(color), value(value)
{

}


Card::~Card()
{

}

int Card::getColor()
{
	return color;
}

int Card::getValue()
{
	return value;
}

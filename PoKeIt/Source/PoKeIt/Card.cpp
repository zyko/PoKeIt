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

// overriding operator> for sorting with std::sort (descending order)
bool Card::operator > (const Card& card) const
{
	return (value > card.value);
}
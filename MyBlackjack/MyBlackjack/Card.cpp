#include "stdafx.h"
#include "Card.h"

void Card::set(int n, Suit s)							// установка значения
{
	suit = s; number = n;
}

void Card::display() const
{
	if (number >= 2 && number <= 10)
		cout << number;
	else
	{
		switch (number)
		{
		case jack: cout << 'J'; break;
		case queen: cout << 'Q'; break;
		case king: cout << 'K'; break;
		case ace: cout << 'A'; break;
		}
	}
	switch (suit)
	{
	case clubs: cout << " Clubs "; break;
	case diamonds: cout << " Diamonds "; break;
	case hearts: cout << " Hearts "; break;
	case spades: cout << " Spades "; break;
	}
}

int Card::GetValue() const
{
	if (number >= 2 && number <= 10)
		return number;
	else if (number <= 13)
		return 10;
	else if (number == 14)
		return 11;
}
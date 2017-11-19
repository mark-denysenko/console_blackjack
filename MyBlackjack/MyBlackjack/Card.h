#pragma once
#include <iostream>

enum Suit { clubs, diamonds, hearts, spades };

// от 2 до 10 обычные числа 
const int jack = 11;
const int queen = 12;
const int king = 13;
const int ace = 14;

using namespace std;

class Card
{
public:
	Card() { }
	int GetValue() const;
	void set(int, Suit);			 // установка значения
	void display() const;			 // показ карты
	~Card() { }

private:
	int number;
	Suit suit;
};

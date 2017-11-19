#pragma once
#include <iostream>

enum Suit { clubs, diamonds, hearts, spades };

// �� 2 �� 10 ������� ����� 
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
	void set(int, Suit);			 // ��������� ��������
	void display() const;			 // ����� �����
	~Card() { }

private:
	int number;
	Suit suit;
};

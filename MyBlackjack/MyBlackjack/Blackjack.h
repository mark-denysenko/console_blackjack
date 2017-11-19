#pragma once

#include "Player.h"
#include "Card.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <dos.h>
#define SEC 1000

class Blackjack
{
public:
	void MakingDeck();
	Blackjack();
	void MakeBet();
	void PlayMatch();
	void FirstDistribution();
	void TakingAdditionalCard();
	~Blackjack();
	Card TakeCard();					// int TakeCard();
	void Shuffle();
	void ShowDeck();
	void FinalCalculation();
	void Clear();
	ofstream file;

private:
	short computer_players;			
	unsigned char Number_of_card;
	unsigned char Dealer_hide_card;
	Card deck[52];
	Player Human;
	Player Dealer;
	Player *Computer;
};
#pragma once
#include <iostream>
#include <vector>
#include "Card.h"

class Player
{
public:
	Player();
	void SetBet(int);
	int GetPoints() const;			// test
	int GetChips() const;
	void SetPoints(int);
	void AddPoints(int);
	void AddCard(Card&);			// test function
	void ChangeChips(int);
	void Win();
	void GotBlackjack();
	void Lose();
	~Player();

private:
	int points,
		current_bet,
		chips;		  // фишки	
	vector <Card> cards;

};
#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	chips = 100;			// starting money
	current_bet = 0;
	points = 0;
}

Player::~Player()
{
}

void Player::SetBet(int bet)
{
	this->current_bet = bet;
}

int Player::GetPoints() const
{
	short ace_value = 0,
		  total_points = 0;

	for (int i = 0; i < cards.size(); i++)
	{
		Card c = cards[i];
		if (c.GetValue() == 11) ace_value++;
		total_points += c.GetValue();
	}
	while (ace_value && (total_points > 21))
	{
		ace_value--;
		total_points -= 10;
	}

	return total_points;
	//return this->points;
}

void Player::SetPoints(int p)
{
	this->points = p;
}

void Player::AddPoints(int p)
{
	this->points = this->points + p;
}

int Player::GetChips() const
{
	return this->chips;
}

void Player::AddCard(Card &newCard)
{
	this->cards.push_back(newCard);
}

void Player::ChangeChips(int money)
{
	this->chips = this->chips + money;
}

void Player::Win()
{
	std::cout << "\nCONGRATULATION!!! YOU WIN " << this->current_bet << " - your gain" << std::endl;
	this->chips += current_bet;
	current_bet = 0;
	points = 0;
}

void Player::GotBlackjack()
{
	std::cout << "\nCONGRATULATION!!! YOU HAVE GOT __BLACKJACK__ " << this->current_bet * 3 << " - your gain" << std::endl;
	this->chips += (2*current_bet);
	current_bet = 0;
	points = 0;
}

void Player::Lose()
{
	std::cout << "\nYou lost in this game. Next time will luck)" << std::endl;
	this->chips -= current_bet;
	current_bet = 0;
	points = 0;
}
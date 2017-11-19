// MyBlackjack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Blackjack.h"
#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "----------------------- B L A C K J A C K -----------------------\n";
	cout << "-----------------------  _ _ _ _21 _ _ _ _-----------------------\n";
	cout << "-----------------------     O C H K O     -----------------------\n";
	cout << "Starting coins - 100. Dealer - computer. Rules - classical.\n";
	Blackjack Game;
	char answer = 'y';
	while (answer == 'y' || answer == 'Y')
	{
		Game.Shuffle();
		Game.PlayMatch();
		std::cout << "\nDo you want play new match?( y - yes, n - no): "; cin >> answer;
	}
	cout << "_______________________  B Y E !   B Y E ! ______________________\n";
	system("pause");
    return 0;
}


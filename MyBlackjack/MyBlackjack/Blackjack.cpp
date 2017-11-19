#include "stdafx.h"
#include "Blackjack.h"

Blackjack::Blackjack()
{
	file.open("TextProcess.txt", ios::out | ios::app);
	int players = 0;
	cout << "Input additional players (computers) max - 6, 0 - play only with dealer: ";
	cin >> players;
	while (true)
	{
		if (players > 6 || players < 0)
		{
			cout << "Invalid value!!! Try again: ";
			cin >> players;
		}
		else if (players == 0) break;
		else
		{
			Computer = new Player[players];
			break;
		}
	}
	Number_of_card = 0;
	computer_players = players;
	MakingDeck();
}

Blackjack::~Blackjack()
{
	file.close();
	if (computer_players != 0) delete[] Computer;
}

void Blackjack::MakingDeck()
{
	for (int j = 0; j < 52; j++)   // создаем упорядоченную колоду карт
	{
		int num = (j % 13) + 2;
		Suit su = Suit(j / 13);
		deck[j].set(num, su);
	}
}

void Blackjack::ShowDeck()
{
	for (int j = 0; j < 52; j++)
	{
		deck[j].display();
		cout << "  ";
		if (!((j + 1) % 13))	  // начинаем новую строку после каждой 13-й карты
			cout << endl;
	}
}

void Blackjack::Shuffle()
{
	srand(time(NULL));
	int k;
	Card temp;
	for (int j = 0; j < 52; j++) // рандомно меняем местами карты 156 раз в колоде из 52 карт
	{
		k = rand() % 52;		 // выбираем случайную карту
		temp = deck[j];			 // и меняем ее с текущей
		deck[j] = deck[k];
		deck[k] = temp;
	}
}

void Blackjack::MakeBet()
{
	int bet = 0;
	cout << "Make a bet: "; cin >> bet;
	while (true)
	{
		if (bet > Human.GetChips() || bet < 1)
		{
			std::cout << "Invalid number or you do not have money! Try again: ";
			std::cin >> bet;
		}
		else break;
	}

	file << "\nHuman make bet: " << bet;
	Human.SetBet(bet);
}

void Blackjack::PlayMatch()
{
	time_t t;
	t = time(0);
	file << "\n\nStart Match - " << ctime(&t) << "Player, dealer + " << computer_players << " computers\n";

	MakeBet();

	FirstDistribution();

	TakingAdditionalCard();

	_sleep(3 * SEC);
	FinalCalculation();

	Clear();
}

void Blackjack::FirstDistribution()
{
	std::cout << "Your`s cards: ";
	_sleep(SEC);
	//Human.AddPoints(TakeCard());
	Human.AddCard(TakeCard());
	_sleep(SEC);
	//Human.AddPoints(TakeCard());
	Human.AddCard(TakeCard());
	std::cout << " (total score = " << Human.GetPoints() << ")\n"; _sleep(2 * SEC);
	file << "\nHuman`s score after 1-st distribution: " << Human.GetPoints();
	if (computer_players > 0)
	{
		for (int i = 0; i < computer_players; i++)
		{
			std::cout << i + 1 << " computer`s cards: ";
			//Computer[i].AddPoints(TakeCard());
			//Computer[i].AddPoints(TakeCard());
			Computer[i].AddCard(TakeCard());
			Computer[i].AddCard(TakeCard());
			std::cout << " (total score = " << Computer[i].GetPoints() << ")\n";
			file << "\nComputer`s "<< i + 1 << " score after 1-st distribution: " << Computer[i].GetPoints();
		}
	}
	std::cout << "Dealer`s cards: ??? ";
	Dealer.AddCard(deck[Number_of_card]);
	Dealer_hide_card = Number_of_card;
	Number_of_card++;
	_sleep(SEC);
	//Dealer.AddPoints(TakeCard());
	Dealer.AddCard(TakeCard());
	//std::cout << " (total score = ??? + " << Dealer.GetPoints() << ")\n";
	std::cout << " (total score = ??? + " << deck[Number_of_card - 1].GetValue() << ")\n";
	file << "\nDealer`s score after 1-st distribution: " << Dealer.GetPoints() + deck[Dealer_hide_card].GetValue();
}

void Blackjack::TakingAdditionalCard()
{
	char  answer = 'y';
	while (answer == 'y' || answer == 'Y')
	{
		std::cout << "\nDo you want take one more card? (y - yes, n - no):";
		std::cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			std::cout << "Additional card: ";
			//Human.AddPoints(TakeCard());
			Human.AddCard(TakeCard());
			std::cout << " (total score = " << Human.GetPoints() << ")\n";
			if (Human.GetPoints() > 21) { std::cout << "\nYou have got more than 21!!!\n"; break; }
			if (Human.GetPoints() == 21) { std::cout << "\nYou have got 21!!! N I C E"; break; }
		}
	}
	if (computer_players > 0)
	{
		std::cout << std::endl;
		for (int i = 0; i < computer_players; i++)
		{
			std::cout << i + 1 << " computer take additional cards: ";
			while (true)
			{
				//if (Computer[i].GetPoints() < 17) Computer[i].AddPoints(TakeCard());
				if (Computer[i].GetPoints() < 17) Computer[i].AddCard(TakeCard());
				else break;
			}
			std::cout << " (total score = " << Computer[i].GetPoints() << ")\n";
		}
	}
	std::cout << "\nDealer: HIDDEN CARD was ";
	_sleep(SEC);
	deck[Dealer_hide_card].display(); // Dealer.AddPoints(deck[Dealer_hide_card].GetValue());
	std::cout << " (total score = " << Dealer.GetPoints() << ")\n";
	if (Dealer.GetPoints() < 17)
	{
		std::cout << "Dealer's additional card: "; _sleep(SEC);
		//while (Dealer.GetPoints() < 17) Dealer.AddPoints(TakeCard());
		while (Dealer.GetPoints() < 17) Dealer.AddCard(TakeCard());
		std::cout << " (total score " << Dealer.GetPoints() << ")\n";
	}
}

//int Blackjack::TakeCard()
Card Blackjack::TakeCard()
{
	deck[Number_of_card].display();
	// return deck[Number_of_card++].GetValue();
	return deck[Number_of_card++];
}

void Blackjack::FinalCalculation()
{
	int Dealer_score = Dealer.GetPoints();
	std::cout << std::endl;
	file << "\n---------------RESULT---------------";
	file << "\nDealer`s score: " << Dealer_score;
	file << "\nHuman`s score: " << Human.GetPoints();
	for (int i = 0; i < computer_players; i++)
	{
		if ((Dealer_score <= Computer[i].GetPoints() && Computer[i].GetPoints() <= 21) || (21 < Dealer_score && Computer[i].GetPoints() < 21)) 
			std::cout << i + 1 << " computer WIN!!!\n";
		else std::cout << i + 1 << " computer LOSE!!!\n";
		file << "\nComputer`s " << i + 1 << " score: " << Computer[i].GetPoints();
	}
	if ((Human.GetPoints() >= Dealer_score && Human.GetPoints() < 21) || (21 < Dealer_score && Human.GetPoints() < 21)) Human.Win();
		else if (Human.GetPoints() == 21) Human.GotBlackjack();
			else if (Human.GetPoints() > 21 || (Human.GetPoints() < Dealer.GetPoints() && Human.GetPoints() < 21)) Human.Lose();
}

void Blackjack::Clear()
{
	Number_of_card = 0;
	Dealer.SetPoints(0);
	for (int i = 0; i < computer_players; i++)
	{
		Computer[i].SetPoints(0);
	}
}
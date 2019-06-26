#pragma once

#include <iostream>

#include "Hand.h"

int readInt()
{
	int val;

	while (!(std::cin >> val).good() || val < 0)
	{
		if (!(std::cin.good()))
		{
			std::cout << "Please enter a numeric value! ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (val < 0)
			std::cout << "Please enter a positive number! ";
	}

	return val;
}

bool readBool()
{
	char val;

	while (!(std::cin >> val).good() || val != 'y' && val != 'n')
	{
		std::cout << "Please enter 'y' or 'n'! ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	if (val == 'n')
		return false;

	return true;
}

bool continueGame()
{
	std::cout << "Would you like to continue? (y/n) ";

	return readBool();
}

int getBet()
{
	std::cout << "How much you would like to bet? ";

	return readInt();
}

int placeBet(int& wallet)
{
	std::cout << "You have " << wallet << " coins." << std::endl;

	int bet = getBet();

	while (bet > wallet)
	{
		std::cout << "You don't have enough coins!" << std::endl;

		bet = getBet();
	}

	wallet -= bet;

	return bet;
}

void addCoins(int& wallet, int bet)
{
	wallet += bet;

	std::cout << "You have " << wallet << " coins." << std::endl;
}

bool playerDraws()
{
	std::cout << "Would you like to draw a card? (y/n) ";

	return readBool();
}

void printHandValue(const Hand& hand)
{
	std::cout << "Your hand is worth " << hand.getHandValue() << "." << std::endl;
}

void printDealerValue(const Hand& hand)
{
	std::cout << "Dealer's hand is worth " << hand.getHandValue() << "." << std::endl;
}

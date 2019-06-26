#include <iostream>

#include "game_functions.h"
#include "Hand.h"

const int starterCoins = 100;
const int dealerDrawValueLimit = 16;
const int starterHandSize = 2;

// Simple Blackjack with 52 cards and one player against the Dealer

int main()
{
	Hand dealer;
	Hand player;
	int playerWallet = starterCoins;

	// Game lasts until wallet is empty or the player does not wish to continue

	do
	{	
		// Creates shuffled deck

		auto deck = Deck::create();

		// Participants discard down to zero

		player.discardCards();
		dealer.discardCards();

		std::cout << "New round!" << std::endl;

		// Starting bet

		int bet = placeBet(playerWallet);

		// Initial draw for player added to hand

		Card nextDraw = deck.draw();

		std::cout << "Player got card: " << nextDraw.toString() << std::endl;
		
		player.addCard(nextDraw);

		// Initial draw for Dealer added to hand

		nextDraw = deck.draw();

		std::cout << "Dealer got card: " << nextDraw.toString() << std::endl;

		dealer.addCard(nextDraw);

		nextDraw = deck.draw();

		// Completes starter hand for player

		std::cout << "Player got card: " << nextDraw.toString() << std::endl;

		player.addCard(nextDraw);

		// Completes starter hand for Dealer, face down according to the rules

		Card faceDownCard = deck.draw();

		std::cout << "Dealer got a face down card." << std::endl;

		dealer.addCard(faceDownCard);

		printHandValue(player);

		// Player draws until bust, maximum hand size reached or stops

		while (player.getHandValue() <= maxValidHandValue && player.size() < 5 && playerDraws())
		{
			nextDraw = deck.draw();

			std::cout << "Player got card: " << nextDraw.toString() << std::endl;

			player.addCard(nextDraw);

			printHandValue(player);
		}

		// Player busts if hand value is over 21

		if (player.getHandValue() > maxValidHandValue)
		{
			std::cout << "You have lost this round with a bust!" << std::endl;

			continue;
		}

		// Dealer reveals second card and draws until bust, maximum hand size or Dealer value limit reached

		std::cout << "Dealer's face down card is " << faceDownCard.toString() << std::endl;

		while (dealer.getHandValue() <= dealerDrawValueLimit && dealer.size() < 5)
		{
			nextDraw = deck.draw();

			std::cout << "Dealer got card: " << nextDraw.toString() << std::endl;

			dealer.addCard(nextDraw);
		}

		printDealerValue(dealer);

		// Dealer busts if hand value is over 21

		if (dealer.getHandValue() > maxValidHandValue)
		{
			std::cout << "The dealer have lost this round with a bust! You have won!" << std::endl;

			addCoins(playerWallet, bet * 2);

			continue;
		}

		// Player wins with higher value

		if (dealer.getHandValue() < player.getHandValue())
		{

			// Player winnings increase with Blackjack (value of 21 with two cards)

			if (player.size() == starterHandSize && player.getHandValue() == maxValidHandValue)
			{
				std::cout << "You have won this round with a Blackjack!" << std::endl;
				
				addCoins(playerWallet, bet * 3 / 2);
			}
			else
			{
				std::cout << "You have won this round!" << std::endl;

				addCoins(playerWallet, bet * 2);
			}

			continue;
		}

		// Dealer wins with higher value

		if (dealer.getHandValue() > player.getHandValue())
		{	
			std::cout << "The dealer have won this round!" << std::endl;

			continue;
		}

		// Draw 

		if (player.getHandValue() < maxValidHandValue || (player.size() == starterHandSize && dealer.size() == starterHandSize))
		{
			std::cout << "Draw!" << std::endl;

			addCoins(playerWallet, bet);
			
			continue;
		}

		// Player has Blackjack and Dealer has hand value of 21

		if (player.size() == starterHandSize && dealer.size() > starterHandSize)
		{
			std::cout << "You have a Blackjack!" << std::endl;

			addCoins(playerWallet, bet * 3 / 2);

			continue;
		}

		// Dealer has Blackjack and player has hand value of 21

		if (dealer.size() == starterHandSize && player.size() > starterHandSize)
		{
			std::cout << "Dealer has a Blackjack!" << std::endl;
		}
	}
	while (playerWallet > 0 && continueGame());

	// Message on exit

	std::cout << "You have finished the game with " << playerWallet << " coins." << std::endl;

	return 0;
}


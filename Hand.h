#pragma once

#include <random>
#include <vector>

#include "Card.h"
#include "Deck.h"

const int maxCardsInDeck = 5;
const int maxValidHandValue = 21;

class Hand
{
public:
	Hand()
	{}

	size_t size() const
	{
		return cards.size();
	}

	bool isEmpty() const
	{
		return size() == 0;
	}

	void addCard(const Card& card)
	{
		if (size() < maxCardsInDeck)
		{
			cards.push_back(card);
		}
	}

	void discardCards()
	{
		cards.clear();
	}

	int getHandValue() const
	{
		int sum = 0;
		int aceCount = 0;

		for (const Card& card : cards)
		{
			sum += card.getValue();

			if (card.getFace() == Face::Ace)
				++aceCount;
		}

		while (sum > maxValidHandValue && aceCount > 0)
		{
			sum -= defaultAceValue;
			sum += reducedAceValue;
			
			--aceCount;
		}

		return sum;
	}

private:
	std::vector<Card> cards;
};

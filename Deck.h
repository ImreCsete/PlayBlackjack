#pragma once

#include <algorithm>
#include <deque>
#include <random>
#include <vector>

#include "Card.h"

class Deck
{
	Deck()
		: cards()
	{}
	
	void addCard(Suit suit, Face face)
	{
		cards.push_back(Card(suit, face));
	}

	void shuffle()
	{
		std::random_device random;
		std::mt19937 rng(random());

		std::shuffle(cards.begin(), cards.end(), rng);
	}

public:
	size_t size() const
	{
		return cards.size();
	}

	bool isEmpty() const
	{
		return size() == 0;
	}

	Card draw()
	{
		auto back = cards.back();

		cards.pop_back();

		return back;
	}

	static Deck create()
	{
		Deck deck;
		
		for (const auto& suit : allSuits)
		{
			for (const auto& face : allFaces)
			{
				deck.addCard(suit.first, face.first);
			}
		}
		
		deck.shuffle();

		return deck;
	}

private:
	std::deque<Card> cards;
};

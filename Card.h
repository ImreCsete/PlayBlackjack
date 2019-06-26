#pragma once

#include <map>
#include <string>

enum class Suit
{
	None = 0,
	Spades,
	Clubs,
	Hearts,
	Diamonds
};

enum class Face
{	
	None = 0,
	Ace = 1,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King
};

const static std::map<Suit, std::string> allSuits =
{
	{Suit::Spades, "Spades"},
	{Suit::Clubs, "Clubs"},
	{Suit::Hearts, "Hearts"},
	{Suit::Diamonds, "Diamonds"}
};

const static std::map<Face, std::string> allFaces =
{
	{Face::Ace, "Ace"},
	{Face::Two, "Two"},
	{Face::Three, "Three"},
	{Face::Four, "Four"},
	{Face::Five, "Five"},
	{Face::Six, "Six"},
	{Face::Seven, "Seven"},
	{Face::Eight, "Eight"},
	{Face::Nine, "Nine"},
	{Face::Ten, "Ten"},
	{Face::Jack, "Jack"},
	{Face::Queen, "Queen"},
	{Face::King, "King"}
};

const int defaultCardValue = 10;
const int defaultAceValue = 11;
const int reducedAceValue = 1;

class Card
{
	Suit suit_;
	Face face_;

public:
	Card()
		: suit_(Suit::None), face_(Face::None)
	{}

	Card(Suit suit, Face face)
		: suit_(suit), face_(face)
	{}

	Suit getSuit() const { return suit_; }
	Face getFace() const { return face_; }

	int getValue() const
	{
		if (face_ >= Face::Two && face_ <= Face::Ten)
			return static_cast<int>(face_);
		
		if (face_ == Face::Ace)
			return defaultAceValue;

		return defaultCardValue;
	}

	std::string toString() const
	{
		return allFaces.at(face_) + " of " + allSuits.at(suit_);
	}
};

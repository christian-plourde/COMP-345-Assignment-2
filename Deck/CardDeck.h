#ifndef CARDDECK_H
#define CARDDECK_H

#include "Card.h"
#include "../Graph/SinglyLinkedList.h"
//#include "SinglyLinkedList.h"

class CardDeck
	// class that represents a deck of cards
{
	const static int NUMBER_OF_SPECIAL_CARDS = 2;			// number of special cards
	const static int NUMBER_OF_CARDS = 64;					// number of cards
private:
	Card specialCards[NUMBER_OF_SPECIAL_CARDS];				// array to hold special cards
	Card cardDeck[NUMBER_OF_CARDS];							// array that initally creates cards, used to shuffle deck
	SinglyLinkedList<Card>* cardDeckList;					// deck of cards
	SinglyLinkedList<Card>* discardedCards;					// deck of discarded cards 

public:
	CardDeck();			// constructor
	~CardDeck();		// destructor

	SinglyLinkedList<Card>* getDeck();				// returns pointer to deck of cards
	SinglyLinkedList<Card>* getDiscardedDeck();		// returns pointer to deck of discarded cards 

	void Print(SinglyLinkedList<Card>*);			// prints a deck of cards in a table
	void Shuffle();									// shuffles the deck
	bool isEmptyDeck();								// check whether deck of cards is empty
	bool isEmptyDiscardedDeck();					// check whether deck of discarded cards is empty
	Card SelectACard(SinglyLinkedList<Card>*);		// select a card from a deck
	void discardCard(Card, SinglyLinkedList<Card>*); // discard a card to a deck
};
#endif
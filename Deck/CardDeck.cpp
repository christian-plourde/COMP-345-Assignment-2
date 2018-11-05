// implementation file for CardDeck.h

#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include<sstream>
#include "CardDeck.h"
using namespace std;

int stringToInt(string);			// converts a string holding an integer to an integer
HowTo stringToHowTo(string);		// gets a how to representation from a string
int longestNameSize = 0;			// holds longest card name size for table print function

// card deck default constructor
CardDeck::CardDeck() {
	cardDeckList = new SinglyLinkedList<Card>();
	discardedCards = new SinglyLinkedList<Card>();
	string fname = "cards.csv";							// file name holding all information about cards
	string i, n, c, h, e;								// holds information when reading from cards file
	ifstream file(fname);								// sets up to open card file
	int count = 0;										// current index in array
	if (file) {												// if file can be opened
		for (int j = 0; j < NUMBER_OF_SPECIAL_CARDS; j++)		// create special cards
		{
			getline(file, i, ',');
			specialCards[j].setID(stringToInt(i));
			getline(file, n, ',');
			specialCards[j].setName(n);
			getline(file, c, ',');
			specialCards[j].setCost(stringToInt(c));
			getline(file, h, ',');
			specialCards[j].setHowTo(stringToHowTo(h));
			getline(file, e);
			specialCards[j].setEffect(e);
			/*if (n.size() > longestNameSize)
				longestNameSize = n.size();*/
		}
		while (getline(file, i, ',')) {				// while still cards to create, create them
			cardDeck[count].setID(stringToInt(i));
			getline(file, n, ',');
			cardDeck[count].setName(n);
			getline(file, c, ',');
			cardDeck[count].setCost(stringToInt(c));
			getline(file, h, ',');
			cardDeck[count].setHowTo(stringToHowTo(h));
			getline(file, e);
			cardDeck[count].setEffect(e);
			count++;									// move to next card (array position)
			if (n.size() > longestNameSize)				// find longest name, for print function
				longestNameSize = n.size();
		}
		file.close();			// finished with file, so close
	}
	else {                                      // file cannot be opened
		cout << "ERROR: FAILURE TO OPEN FILE, exiting..." << endl;
		system("pause");
		exit(1);
	}

	Shuffle();				// shuffle the deck twice for more randomness
	Shuffle();

	// take all cards from array and insert them into linked list
	for (int i = 0; i < NUMBER_OF_CARDS; i++) {
		node<Card> *nodes = new node<Card>();
		nodes->setData(cardDeck[i]);
		cardDeckList->addLast(nodes);
	}
}

// converts a string holding an integer to an integer
int stringToInt(string n) {
	stringstream num(n);
	int x;
	num >> x;
	return x;
}

// converts a string holding an how to to a how to enum
HowTo stringToHowTo(string h) {
	int x = stringToInt(h);
	switch (x) {
	case 0: return Empty; break;
	case 1: return Goal; break;
	case 2: return Keep; break;
	default: return Discard;
	}
}

// destructor
CardDeck::~CardDeck() {

	delete cardDeckList;
	delete discardedCards;
}

// return pointer to deck of cards
SinglyLinkedList<Card>* CardDeck::getDeck() {
	return cardDeckList;
}

// return pointer to deck of discarded cards
SinglyLinkedList<Card>* CardDeck::getDiscardedDeck() {
	return discardedCards;
}

// print deck of cards in table format
void CardDeck::Print(SinglyLinkedList<Card> *list) {
	if (list->getCount() == 0)			// deck empty so no need to print
		cout << "Deck is empty\n";
	else {
		cout << "  ID  |";
		for (int i = 0; i < (longestNameSize - 4) / 2; i++)			// adjust name column to fit card with longest name
			cout << " ";
		cout << " NAME ";
		for (int i = 0; i < (longestNameSize - 4) / 2 + 1; i++)
			cout << " ";
		cout << "|  COST  " << endl;
		node<Card> *n = list->getHead();				// starting at beginning of deck
		Card c;
		for (int i = 0; i < list->getCount(); i++) {		// print all cards in the deck
			c = n->getData();
			int id = c.getID();
			cout << "  ";
			if (id < 10)
				cout << id << "  ";		// print one more space if single id, to pad correctly
			else
				cout << id << " ";
			string name = c.getName();
			int size = name.size();
			cout << " | " << name;
			for (int j = size; j <= longestNameSize; j++)		// pad remaning space between current card name and longest card name to keep table drawn correctly
				cout << " ";
			cout << " |   " << c.getCost() << endl;
			n = n->getNext();							// get next card
		}
	}
}

// shuffles the deck
void CardDeck::Shuffle() {
	srand(time(0));

	for (int i = 0; i < NUMBER_OF_CARDS; i++)
		swap(cardDeck[i], cardDeck[rand() % NUMBER_OF_CARDS]);
}


// returns whether card deck is empty
bool CardDeck::isEmptyDeck() {
	if (cardDeckList->getCount() == 0)
		return true;
	return false;
}

// returns whether discarded card deck is empty
bool CardDeck::isEmptyDiscardedDeck() {
	if (discardedCards->getCount() == 0)
		return true;
	return false;
}

// removes card from head of specified linked list and returns said card
Card CardDeck::SelectACard(SinglyLinkedList<Card>* list) {
	node<Card> *c = list->getHead();
	Card card = c->getData();
	list->remove(c);
	return card;
}

// adds card c to tail of specified linked list
void CardDeck::discardCard(Card c, SinglyLinkedList<Card>* list) {
	node<Card> *n = new node<Card>();
	n->setData(c);
	list->addLast(n);
}
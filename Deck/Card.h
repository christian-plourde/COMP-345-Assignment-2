#ifndef CARD_H
#define CARD_H
#include <string>
using namespace std;

enum HowTo { Empty, Goal, Keep, Discard };		// possible how tos of cards

class Card {
	// a class to hold information about each card
private:
	int id;						// id of the card
	string name;				// name of the card
	int cost;					// cost in energy of the card
	HowTo howTo;				// how to of the card
	string effect;				// effect of the card

public:
	Card();											// default constructor
	Card(int, string, int, HowTo, string);			// set constructor
	~Card();										// destructor

	void setID(int);							// set id of card
	void setName(string);						// set cards name
	void setCost(int);							// set cards energy cost
	void setHowTo(HowTo);						// set cards how to
	void setEffect(string);						// set cards effect

	int getID() const;							// get id of card
	string getName() const;						// get name of card
	int getCost() const;						// get energy cost of card
	HowTo getHowTo() const;						// get cards how to
	string getEffect() const;					// get effect of card

	void Print();								// nice print of card
};

#endif
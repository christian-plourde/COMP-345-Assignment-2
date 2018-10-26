#ifndef MONSTER_H
#define MONSTER_H
#include "../Player/Characters.h"
using namespace std;


class Monsters {
	// class that represents a monster
private:
	Characters name;					// enum represnting name of monster
	int victoryPoints;					// number of victory points monster has
	int health;							// number of health monster has

public:
	Monsters();							// default constructor
	Monsters(Characters, int, int);		// set constructor
	~Monsters();						// destructor

	void setName(Characters);			// set name of monster using enum
	void setVictoryPoints(int);			// set victory points of monster
	void setHealth(int);				// set health of monster

	Characters getName() const;			// get enum of name of monster
	int getVictoryPoints() const;		// get victory points of monster
	int getHealth() const;				// get health of monster

	void Print();						// print information about monster
};
#endif
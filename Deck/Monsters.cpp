// implementation file for Monsters.h


#include <iostream>
#include "Monsters.h"

string characters[7] = { "Captain Fish", "Sheriff", "Mantis", "Rob", "Drakonis", "Kong", "None" };		// string representation of the Characters enum

// default constructor
Monsters::Monsters() {
	name = None;
}

// set constructor, creating a monster with known parameters
Monsters::Monsters(Characters nam, int vp, int heal) {
	name = nam;
	victoryPoints = vp;
	health = heal;
}

Monsters::~Monsters() {
	// destructor
}

/*** SETTERS ***/
void Monsters::setName(Characters nam) {
	name = nam;
}

void Monsters::setVictoryPoints(int vp) {
	victoryPoints = vp;
}

void Monsters::setHealth(int heal) {
	health = heal;
}

/*** GETTERS ***/
Characters Monsters::getName() const {
	return name;
}

int Monsters::getVictoryPoints() const {
	return victoryPoints;
}

int Monsters::getHealth() const {
	return health;
}

// print information about a monster
void Monsters::Print() {
	cout << "{ Monster: " << characters[name] << endl;
	cout << "  Victory Points: " << victoryPoints << endl;
	cout << "  Health: " << health << " }" << endl;
}
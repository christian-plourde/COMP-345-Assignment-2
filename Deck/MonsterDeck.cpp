// implementation file for MonsterDeck.h


#include <iostream>
#include "MonsterDeck.h"

// monster deck default constructor
MonsterDeck::MonsterDeck() {
	Monsters monster;				// create inital monster
	monster.setVictoryPoints(0);	// with correct victory points and health
	monster.setHealth(10);			// as only thing that changes is name

	int count = 0;		// position to place monster into the monster deck

	for (Characters charac = CaptainFish; charac < None; charac = static_cast<Characters>(charac+1)) {		// loop through all the monster name characters enum
		monster.setName(charac);			// set name for this character
		monsterDeck[count] = monster;		// add monster to the monster deck
		count++;							// move to next position in the deck
	}
}

MonsterDeck::~MonsterDeck() {
	// destructor
}

// returns a monster in the deck with the character enum c
Monsters MonsterDeck::getMonster(Characters c) {
	for (Monsters m : monsterDeck) {
		if (m.getName() == c)
			return m;
	}
}

// returns integer position of monster object in the deck
int MonsterDeck::getMonsterPosition(Characters c) {
	for (int i = 0; i < NUMBER_OF_MONSTERS; i++) {
		if (monsterDeck[i].getName() == c)
			return i;
	}
	return -1;
}

// updates a monster in the deck with the set victory points and health
bool MonsterDeck::updateMonster(Characters c, int vp, int heal) {
	int i = getMonsterPosition(c);
	if (i == -1)
		return false;
	monsterDeck[i].setVictoryPoints(vp);
	monsterDeck[i].setHealth(heal);
	return true;
}

// prints all monsters in the deck
void MonsterDeck::Print() {
	for (Monsters m : monsterDeck)
		m.Print();
}
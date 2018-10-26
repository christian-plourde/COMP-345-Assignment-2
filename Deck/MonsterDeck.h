#ifndef MONSTERDECK_H
#define MONSTERDECK_H
#include "Monsters.h"

class MonsterDeck {
	// class that holds the monster cards
	const static int NUMBER_OF_MONSTERS = 6;			// number of monsters
	private:
		Monsters monsterDeck[NUMBER_OF_MONSTERS];		// array to hold monster

	public:
		MonsterDeck();						// constructor
		~MonsterDeck();						// destructor

		Monsters getMonster(Characters);	// returns monster with Characters enum as name
		int getMonsterPosition(Characters);			// returns position of monster with name Characters enum
		bool updateMonster(Characters, int, int);	// updates monsters victory points and health with name Characters enum

		void Print();						// print information about each monster
};
#endif
// implementation file for TileDeck.h


#include <iostream>
#include <string>
#include <time.h>
#include "Tile.h"
#include "TileDeck.h"
using namespace std;

const int NUMBER_OF_TILES = 45;							// constant number of tiles
Tile TileDeck::tileDeck[NUMBER_OF_TILES];				// array to hold all the tiles

// default constructor
TileDeck::TileDeck()
{
	int i = 0;
	currentTile = 0;
	for (i; i < 15; i++) {						// creates an even amount of high-rise tiles ranging from 1 to 3 durability
		tileDeck[i].setBuilding(HighRise);
		if (i < 5) {
			tileDeck[i].setDurability(1);
			tileDeck[i].setUnit(Infantry);
			tileDeck[i].setReward(1);
			tileDeck[i].setZone(0);
		}
		else if (i < 10) {
			tileDeck[i].setDurability(2);
			tileDeck[i].setUnit(Jet);
			tileDeck[i].setReward(2);
			tileDeck[i].setZone(2);
		}
		else {
			tileDeck[i].setDurability(3);
			tileDeck[i].setUnit(Tank);
			tileDeck[i].setReward(3);
			tileDeck[i].setZone(3);
		}
		tileDeck[i].setRewardType(star);
		tileDeck[i].setisUnit(false);
	}

	for (i; i < 30; i++) {						// creates an even amount of power plant tiles ranging from 1 to 3 durability
		tileDeck[i].setBuilding(PowerPlant);
		if (i < 20) {
			tileDeck[i].setDurability(1);
			tileDeck[i].setUnit(Infantry);
			tileDeck[i].setReward(1);
			tileDeck[i].setZone(8);
		}
		else if (i < 25) {
			tileDeck[i].setDurability(2);
			tileDeck[i].setUnit(Jet);
			tileDeck[i].setReward(2);
			tileDeck[i].setZone(9);
		}
		else {
			tileDeck[i].setDurability(3);
			tileDeck[i].setUnit(Tank);
			tileDeck[i].setReward(3);
			tileDeck[i].setZone(10);
		}
		tileDeck[i].setRewardType(energy);
		tileDeck[i].setisUnit(false);
	}

	for (i; i < 45; i++) {							// creates an even amount of hospital tiles ranging from 1 to 3 durability
		tileDeck[i].setBuilding(Hospital);
		if (i < 30) {
			tileDeck[i].setDurability(1);
			tileDeck[i].setUnit(Infantry);
			tileDeck[i].setReward(1);
			tileDeck[i].setZone(7);
		}
		else if (i < 35) {
			tileDeck[i].setDurability(2);
			tileDeck[i].setUnit(Jet);
			tileDeck[i].setReward(2);
			tileDeck[i].setZone(6);
		}
		else {
			tileDeck[i].setDurability(3);
			tileDeck[i].setUnit(Tank);
			tileDeck[i].setReward(3);
			tileDeck[i].setZone(5);
		}
		tileDeck[i].setRewardType(heart);
		tileDeck[i].setisUnit(false);
	}
	Shuffle();
	Shuffle();
}

TileDeck::~TileDeck() {
	// destructor
}

// shuffles the tile deck
void TileDeck::Shuffle() {
	srand(time(0));

	for (int i = 0; i < NUMBER_OF_TILES; i++)
		swap(tileDeck[i], tileDeck[rand() % NUMBER_OF_TILES]);
}

// returns the tile deck
Tile* TileDeck::getTileDeck()
{
	return tileDeck;
}

// prints every tile in the tile deck
void TileDeck::Print() {
	for (int i = 0; i < NUMBER_OF_TILES; i++)
	{
		tileDeck[i].Print();
	}

}

// returns whether the tile deck is empty
bool TileDeck::EmptyDeck() {
	if (currentTile >= NUMBER_OF_TILES)
		return true;
	return false;
}

// returns the tile at position index of the tile deck
Tile* TileDeck::getTile(int index)
{
	return &tileDeck[index];
}

// returns the tile at tile deck position currentTile
Tile* TileDeck::SelectATile() {
	currentTile++;
	return &tileDeck[currentTile - 1];
}

// turns a building tile into a unit tile
void TileDeck::FlipTile(Tile *t) {

	switch (t->getUnit()) {
	case Infantry: t->setRewardType(heart); break;
	case Jet: t->setRewardType(energy); break;
	case Tank: t->setRewardType(star); break;
	}

	int durability = t->getDurability();
	durability++;
	t->setDurability(durability);

	t->setisUnit(true);
}

// destroys a unit tile
void TileDeck::DestroyTile(Tile *t) {

	//find the tile in the array and set it to null
	for (int i = 0; i < NUMBER_OF_TILES; i++)
	{
		if (&tileDeck[i] == t)
		{
			t->setIsDestroyed(true);
			break;
		}
	}

}
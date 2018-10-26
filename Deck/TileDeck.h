#ifndef TILEDECK_H
#define TILEDECK_h

#include "Tile.h"
#include <cstdlib>

class TileDeck
	// class that represents a deck of Tiles
{
private:
	static Tile tileDeck[];			// array to hold all the tiles
	int currentTile;				// index of tile to get when selecting a tile

public:
	TileDeck();						// constructor
	~TileDeck();					// destructor
	void Print();					// prints all tiles in the tile deck
	void Shuffle();					// shuffles the tiles
	bool EmptyDeck();				// check whether tile deck is empty
	static Tile* getTileDeck();		// gives access to the tile deck
	Tile* SelectATile();			// gets next tile from the tile deck
	Tile* getTile(int);				// returns a tile at index int
	void FlipTile(Tile*);			// turns a tile from building to unit
	void DestroyTile(Tile*);		// destroys a unit tile
};
#endif
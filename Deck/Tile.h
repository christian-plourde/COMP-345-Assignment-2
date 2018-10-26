#ifndef TILE_H
#define TILE_H

#include "../MapLoader/MapLoader.h" //required for the zones
//#include "MapLoader.h"

enum Buildings { HighRise, PowerPlant, Hospital };			// types of buildings
enum Units { Infantry, Jet, Tank };							// types of units
enum Rewards { star, heart, energy };						// types of rewards

class Tile
	// class that represents a Building/Unit Tile
{
private:
	Buildings building;					// type of building of tile
	Units unit;							// type of unit of tile
	int zone;							// borough/zone that tile is assigned to on map
	int durability;						// durability of tile
	int reward;							// number of reward for destroying the tile
	Rewards rewardType;					// type of reward given for destroying
	bool isUnit;						// identifier for whether tile is building or unit
	bool isDestroyed;					// identifier for whether tile has been destroyed

public:
	Tile();															// default constructor
	Tile(Buildings, Units, int, int, int, Rewards, bool);			// set constructor
	~Tile();														// destructor

	void setBuilding(Buildings);				// sets building of tile
	void setUnit(Units);						// sets unit of tile
	void setZone(int);							// sets borough/zone of tile
	void setDurability(int);					// sets durability of tile
	void setReward(int);						// sets number of reward of tile
	void setRewardType(Rewards);				// sets tiles reward type
	void setisUnit(bool);						// sets unit identifier
	void setIsDestroyed(bool);					// sets destroyed identifier

	Buildings getBuilding() const;				// gets building of tile
	Units getUnit() const;						// gets unit of tile
	int getZone() const;						// gets borough/zone of tile
	int getDurability() const;					// gets durability of tile
	int getReward() const;						// gets reward of tile
	Rewards getRewardType() const;				// gets reward type of tile
	bool getIsUnit() const;						// gets unit identifier
	bool getIsDestroyed();						// gets destroyed identifier

	void Print();								// prints information about tile
};
#endif
// implementation file for Tile.h


#include "Tile.h"
#include<iostream>
#include<string>
using namespace std;

string Build[3] = { "High-Rise", "Power Plant", "Hospital" };		// string representation of buildings enum
string Unit[3] = { "Infantry", "Jet", "Tank" };						// string representation of unit enum
string Reward[3] = { "Star", "Heart", "Energy" };					// string representation of reward enum

// default constructor
Tile::Tile() {
	building = HighRise;
	unit = Infantry;
	zone = 0;
	durability = 1;
	reward = 1;
	rewardType = star;
	isUnit = false;
	isDestroyed = false;
}

// set constructor, creating a tile with known parameters
Tile::Tile(Buildings bu, Units un, int zone, int dur, int rew, Rewards rewType, bool isUn) {
	building = bu;
	unit = un;
	this->zone = zone;
	durability = dur;
	reward = rew;
	rewardType = rewType;
	isUnit = isUn;
	isDestroyed = false;
}

Tile::~Tile() {
	// destructor
}

/*** SETTERS ***/
void Tile::setBuilding(Buildings build) {
	building = build;
}

void Tile::setUnit(Units uni) {
	unit = uni;
}

void Tile::setZone(int zone) {

	if (zone >= 0 && zone < MapLoader::getMap()->getVertexCount())
	{
		this->zone = zone;
	}
}

void Tile::setDurability(int dur) {
	durability = dur;
}

void Tile::setReward(int rew) {
	reward = rew;
}

void Tile::setRewardType(Rewards rewType) {
	rewardType = rewType;
}

void Tile::setisUnit(bool type) {
	isUnit = type;
}

void Tile::setIsDestroyed(bool dest)
{
	isDestroyed = dest;
}

/*** GETTERS ***/
Buildings Tile::getBuilding() const {
	return building;
}

Units Tile::getUnit() const {
	return unit;
}

int Tile::getZone() const {
	return zone;
}

int Tile::getDurability() const {
	return durability;
}

int Tile::getReward() const {
	return reward;
}

Rewards Tile::getRewardType() const {
	return rewardType;
}

bool Tile::getIsUnit() const {
	return isUnit;
}

bool Tile::getIsDestroyed()
{
	return isDestroyed;
}

// print information abouta tile
void Tile::Print() {
	cout << "{ Building: " << Build[building] << endl;
	cout << "  Unit: " << Unit[unit] << endl;
	cout << "  Borough: " << MapLoader::getMap()->getVertex(zone)->toString() << endl;		// print borough as a string
	cout << "  Durability: " << durability << endl;
	if (reward > 1)
		cout << "  Reward: " << reward << " " << Reward[rewardType] << "s\n";
	else
		cout << "  Reward: " << reward << " " << Reward[rewardType] << endl;
	cout << boolalpha;		// output following booleans as true, false instead of 1, 0
	cout << " Unit Tile: " << isUnit << endl;
	cout << " Destroyed: " << isDestroyed << " }" << endl;
}
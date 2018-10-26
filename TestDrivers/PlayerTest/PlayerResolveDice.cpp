//this is a test of the roll dice method for the player
#include "../../Player/Player.h"
#include <iostream>
#include "../../Dice/Dice.h"
#include "../../Graph/Graph.h"
#include "../../MapLoader/MapLoader.h"
#include "../../Lib/Exceptions/MasterNodeFullException.h"

int main()
{
  std::cout << "This is a test of the player resolve dice method." << std::endl;

  Player* player = new Player(); //creating a new player
  Player* player2 = new Player(); //creating another player to show the attack effect
  Player* player3 = new Player(); //create another player to simulate the ouch for multiple players in one zone
  MapLoader::setFilePath("map.map");
  MapLoader::loadMap();
  player -> setZone(8); //move the player
  player3 -> setZone(8);

  //in order for the ouch to take effect, we need to make a tile in the players region be a unit
  Tile* tiles = TileDeck::getTileDeck();

  tiles[0].setisUnit(true);
  tiles[0].setZone(8); //make it a unit and place it  in the same zone as player 1
  tiles[1].setisUnit(true);
  tiles[1].setZone(2); //so that player 2 gets hit if we roll three ouch
  //we also need to make a few buildings for the player to destroy
  tiles[2].setZone(8);
  tiles[3].setZone(8);
  tiles[3].setDurability(2);
  tiles[3].setUnit(Jet);

  player -> rollDice(); //roll the dice to then resolve them
  player -> resolveDice(); //resolve the dice


  std::cout << "After resolving the dice: " << std::endl;
  std::cout << player -> toString() << std::endl;
  std::cout << player2 -> toString() << std::endl;
  std::cout << player3 -> toString() << std::endl;

  delete player;
  delete player2;
  delete player3;
  return 0;
}
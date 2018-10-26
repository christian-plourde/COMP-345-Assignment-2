//this is a test of the move method for the player
#include "../../Player/Player.h"
#include <iostream>
#include "../../Dice/Dice.h"
#include "../../Graph/Graph.h"
#include "../../MapLoader/MapLoader.h"
#include "../../Lib/Exceptions/MasterNodeFullException.h"

int main()
{
  std::cout << "This is a test of the player roll move method." << std::endl;

  Player* player = new Player(); //creating a new player

  //for this to work, we need to load the map
  MapLoader::setFilePath("map.map");
  MapLoader::loadMap();

  std::cout << player -> toString() << std::endl;
  player -> move();
  std::cout << player -> toString() << std::endl;
  delete player;
  return 0;
}
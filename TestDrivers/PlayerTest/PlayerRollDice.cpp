//this is a test of the roll dice method for the player
#include "../../Player/Player.h"
#include <iostream>
#include "../../Dice/Dice.h"
#include "../../Graph/Graph.h"
#include "../../MapLoader/MapLoader.h"
#include "../../Lib/Exceptions/MasterNodeFullException.h"

int main()
{
  std::cout << "This is a test of the player roll dice method." << std::endl;

  Player* player = new Player(); //creating a new player
  player -> rollDice();
  delete player;
  return 0;
}
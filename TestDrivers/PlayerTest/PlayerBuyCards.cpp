//this is a test of the buy cards method for the player
#include "../../Player/Player.h"
#include <iostream>
#include "../../Dice/Dice.h"
#include "../../Graph/Graph.h"
#include "../../MapLoader/MapLoader.h"
#include "../../Deck/CardDeck.h"
#include "../../Lib/Exceptions/MasterNodeFullException.h"

int main()
{
  std::cout << "This is a test of the player buy cards method." << std::endl;

  Player* player = new Player(); //creating a new player
  player -> setEnergy(10); //give him some energy so he can actually buy cards

  CardDeck deck;

  player -> buyCards(&deck);
  delete player;
  return 0;
}
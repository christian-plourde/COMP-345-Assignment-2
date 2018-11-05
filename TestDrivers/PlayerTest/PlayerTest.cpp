#include "../../Player/Player.h"
#include <iostream>
#include "../../Dice/Dice.h"
#include "../../Graph/Graph.h"
#include "../../MapLoader/MapLoader.h"
#include "../../Lib/Exceptions/MasterNodeFullException.h"

int main()
{
  std::cout << "This is a test of the player class." << std::endl;

  Player* player = new Player(); //creating a new player
  Player* player2 = new Player(); //creating a new player
  std::cout << player -> toString() << std::endl; //showing details
  std::cout << player2 -> toString() << std::endl; //showing details
  player -> rollDice(); //rolling the dice for player 1
  std::cout << "\n";
  std::cout << "\n";

  MapLoader::setFilePath("../../Maps/map.map"); //load the map since we will need it in order to resolve the dice effects
  MapLoader::loadMap(); // load the map
  std::cout << MapLoader::getMap() -> toString() << std::endl;

  player -> setZone(8); //set the player zone to 8 so that he is outside manhattan while the other is inside
                        //this is so we can test the effect of an attack roll
  player -> resolveDice(); //resolve the dice
  std::cout << player -> toString() << std::endl;
  std::cout << player2 -> toString() << std::endl;

  //now let player 2 roll the dice and resolve them
  player2 -> rollDice();
  player2 -> resolveDice();
  std::cout << player -> toString() << std::endl;
  std::cout << player2 -> toString() << std::endl;

  //now we show the move functionality for player 2
  player2 -> move();

  std::cout << "Moved to: " << MapLoader::getMap() -> getVertex(player2 -> getZone()) -> toString() << std::endl;

  std::cout << player2 -> toString() << std::endl;

  //now let's test the buy cards method
  CardDeck deck;
  deck.Shuffle();

  player2 -> buyCards(&deck);
  std::cout << "Finished" << std::endl;

  /*
  SinglyLinkedList<int>* list = new SinglyLinkedList<int>();
  node<int>* node1 = new node<int>();
  node1 -> setData(1);
  node<int>* node2 = new node<int>();
  node2 -> setData(2);
  node<int>* node3 = new node<int>();
  node3 -> setData(3);
  list -> add(node1);
  //list -> add(node2);
  //list -> add(node3);
  std::cout << list -> toString() << std::endl;
  delete list;
  std::cout << "list deleted" << std::endl;
  */



  delete player;
  player = NULL;
  delete player2;
  player2 = NULL;
  std::cout << "players deleted" << std::endl;
}
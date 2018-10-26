#include "../Dice/Dice.h"
#include "../Player/Player.h"
#include "../MapLoader/MapLoader.h"
#include "../Lib/GameSetupFunctions.h"
#include <iostream>
#include <string>

int main()
{
  //welcome message
  std::cout << "------------------------------" << std::endl;
  std::cout << "|      KING OF NEW YORK      |" << std::endl;
  std::cout << "|    BY CHRISTIAN PLOURDE    |" << std::endl;
  std::cout << "------------------------------" << std::endl;

  MapLoader::setFilePath("D:/C++ Programs/COMP 345/A1/MapLoader/map.map");

  MapLoader::loadMap();

  bool playerCountIsValid = false; // a boolean to store whether or not the playerCount is valid
  int playerCount; //the number of players that will be playing the game

  //first we need to determine how many players will be playing the game
  while (!playerCountIsValid)
  {
    //while the player count is still not valid, keep prompting the user
    try
    {
      playerCount = GameSetupFunctions::getNumberOfPlayers();
      playerCountIsValid = true;
    }

    //catch the number of players that was entered as thrown in function
    catch(int e)
    {
      std::cout << "The number of players should be between 2 and 6. Please try again." << std::endl;
    }

  }

  //now that we have set the number of players playing the game it is time to initialize their player characters
  Player* players = GameSetupFunctions::initializePlayers(playerCount);

  GameSetupFunctions::setPlayerStartZones(playerCount, players, MapLoader::getMap()); //set the zones where the players will begin

  std::cout << "Ready to begin the game!" << std::endl; //ready to start!

  return 0;
}
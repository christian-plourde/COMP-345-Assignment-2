//this file contains some functions that are used to set up a new game
#ifndef GAME_SETUP_FUNCTIONS_H
#define GAME_SETUP_FUNCTIONS_H

#include <iostream>
#include <string>
#include "../Player/Player.h"
#include "StringFunctions.h"
#include "../Player/CharacterMethods.h"
#include "../Graph/Graph.h"
#include "../Graph/SinglyLinkedList.h"
#include "DirectoryFile.h"

namespace GameSetupFunctions
{
  int getNumberOfPlayers(); //a method to get the number of players that will be playing the game
  Player* initializePlayers(int); //a method to initialize a player character, accepts an integer containing the number of players
  void setPlayerStartZones(int, Player*, Graph<std::string>*); //sets the zones in which the players will start the game (int is the number of players)
  void setMap(std::string); //a method for the players to choose the map they wish to play with
  void setPlayerTurnOrder(int, Player*); //a method to set the order that the turns will be taken in
}

#endif
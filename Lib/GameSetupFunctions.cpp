#include "GameSetupFunctions.h"

int GameSetupFunctions::getNumberOfPlayers()
{
  //set the number of players that will be playing the game, assuming the number entered is between 2 and 6
  std::cout << "Please enter the number of players: ";

  int numberOfPlayers = 0; //the number of players

  std::cin >> numberOfPlayers; //set the number of players from the command line

  //if the number of players is greater than 6 or less than 2 then this is not a valid number
  if(numberOfPlayers > 6 || numberOfPlayers < 2)
  {
    throw numberOfPlayers;
  }

  //otherwise, return the valid number of players
  return numberOfPlayers;
}

Player* GameSetupFunctions::initializePlayers(int numberOfPlayers)
{
  //a method to initialize all the player characters that will be playing the game
  //it returns a pointer to a player array that contains all the players

  Player* players = new Player[numberOfPlayers]; //an array to hold all the player objects
  enum Characters* chosenCharacters = new enum Characters[numberOfPlayers]; //an array to hold all the characters that the players have chosen so far
                                                                            //to make sure no character is repeated

  for(int k = 0; k<numberOfPlayers; k++)
  {
    chosenCharacters[k] = None; //initialize all to none
  }

  std::cout << "Choose your characters!" << std::endl;
  std::string playerName; //the name of the new player that will be obtained from command line

  for(int i = 0; i<numberOfPlayers; i++)
  {
    //for each player, set the name of the player
    std::cout << "Player " << (i + 1) << " please enter your name: "; //let the player enter his name
    std::cin >> playerName; //get name input
    players[i].setName(playerName); //set the name of the player
    std::cout << players[i].getName() << "," << " please choose your character: " << std::endl; //now the player must choose his character

    int characterChoice = 1; //simply to print a number of selecting that character

    for(int j = 0; j < 6; j++)
    {
        //output all the characters
        std::cout << characterChoice << ". " << CharacterMethods::characterToString(static_cast<Characters>(j)) << std::endl;
        characterChoice++;
    }

    //we need to make sure that the character that was chosen was not already picked
    //then we ask the player to enter a number corresponding to the character he wants to play as
    bool chosenValid = false; //a boolean to check if the chosen character was valid or not
    int characterChosen = 0; //the character chosen by the player

    while(!chosenValid)
    {
      //ask the player to enter a number corresponding to the character he wants
      try
      {
        //player enters the character number he wants
        std::cout << "Enter the number for the character you would like to be: ";
        std::cin >> characterChosen;

        //if the number is negative or greater than 6, then that value is not valid and we throw an exception
        if(characterChosen < 1 || characterChosen > 6)
        {
          throw characterChosen;
        }

        //we also need to check if that value has already been chosen by another player
        for(int l = 0; l<numberOfPlayers; l++)
        {
          //for each character in the array of chosen characters, check that that character is not equal to the character the player wants
          if(static_cast<int>(chosenCharacters[l]) == characterChosen - 1)
          {
            throw characterChosen;
          }
        }

        //if we made it here without an exception, then we are done
        chosenValid = true; //set this to true so we exit the while loop after we are done setting the character
      }

      catch(int e)
      {
        //catch the thrown integer if there was an exception
        std::cout << "The desired character has already been chosen! Please try again...";
        continue; //restart the process
      }


      //then we need to set the character he has chosen to be his character if it was a valid choice
      players[i].setCharacter(static_cast<Characters>(characterChosen - 1));
      //also modify the entry in the array of already chosen characters
      chosenCharacters[i] = static_cast<Characters>(characterChosen - 1);
    }

  }

  //since we no longer need the array of chosen characters, we need to free up the memory
  delete[] chosenCharacters;
  chosenCharacters = NULL;

  return players;
}

void GameSetupFunctions::setPlayerStartZones(int playerCount, Player* players, Graph<std::string>* graph)
{
  //this is a method to set the start zones for the players based on their choice

  //we need to allow each player to set his start zone

  for(int i = 0; i < playerCount; i++)
  {
    //for each player, list all the zones that are available in the graph and allow him to choose the position that he wants
    //assuming that it is valid

    int vertexCount = 1; //the number that will be placed next to the vertex when giving the player the choice of his start vertex

    //now that all the vertices have been displayed, we need to allow the player to choose the vertex where he wants to start
    std::cout << players[i].getName() << "," << " please select the location where you would like your adventure to begin: " << std::endl;

    for(int j = 0; j < graph -> getVertexCount(); j++)
    {
      //output the vertex that the player can choose from
      std::cout << vertexCount << ". " << graph -> getVertex(j) -> toString() << std::endl;
      vertexCount++; //increment the vertex count so that it is displayed properly in the next iteration
    }

    //we need to check that the vertex he has selected is valid
    bool startIsValid = false; //this will keep track of whether or not he has selected a valid vertex

    while(!startIsValid)
    {
      int startVertex = 0; //the vertex where the player wants to begin
      bool vertexOutOfBounds = false; //a check to see if the vertex is out of bounds
      bool vertexIsInMaster = false; //a check to see if the vertex is in the master zone (i.e. manhattan)

      try
      {
        std::cout << "Please enter a number corresponding to the location you would like to start at: ";
        std::cin >> startVertex; //place the input in the startVertex variable

        if(startVertex < 1 || startVertex > graph -> getVertexCount())
        {
          //if the chosen vertex is outside of the bounds that are acceptable, then throw an error
          vertexOutOfBounds = true; //the vertex is out of bounds
          throw startVertex;
        }

        if(graph -> getVertex(startVertex) -> getData() == "master" || graph -> getVertex(startVertex) -> getData() == "inner")
        {
          //if the requested vertex is a master or inner type vertex that mean it is either manhattan or one of its inner zones
          //the rules state that a player cannot start in manhattan, and therefore these zones are invalid as start zones
          vertexIsInMaster = true;
          throw startVertex;
        }

        //if we made it here without throwing an exception, then our location is valid

        players[i].setZone(startVertex - 1); //set the zone to the one indicated, minus one since in our choices we start at 1

        startIsValid = true; //the user has entered a valid start point
      }

      catch(int e)
      {
        if(vertexOutOfBounds)
        {
          std::cout << "The desired location is not within the game boundaries! Please try again..." << std::endl;
        }

        if(vertexIsInMaster)
        {
          //if the vertex is within the master zone, i.e. manhattan, it is not valid
          std::cout << "The desired location is within the master zone! Please try again..." << std::endl;
        }
      }
    }

  }

}
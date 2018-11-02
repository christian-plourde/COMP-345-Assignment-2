#include "GameSetupFunctions.h"
#include "DirectoryFile.h"
#include "../Dice/DiceFaces.h"
#include "Exceptions/DirectoryNotFoundException.h"
#include "Exceptions/NodeFullException.h"
#include <dirent.h>
#include "../Dice/GreenDice.h"

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

void GameSetupFunctions::initializePlayers(int numberOfPlayers)
{
  //a method to initialize all the player characters that will be playing the game

  enum Characters* chosenCharacters = new enum Characters[numberOfPlayers]; //an array to hold all the characters that the players have chosen so far
                                                                            //to make sure no character is repeated

  for(int k = 0; k<numberOfPlayers; k++)
  {
    chosenCharacters[k] = None; //initialize all to none
  }

  std::cout << "Choose your characters!" << std::endl;
  std::string playerName; //the name of the new player that will be obtained from command line
  Player* newPlayer; //this will point to the player being set up

  for(int i = 0; i<numberOfPlayers; i++)
  {
    //for each player, set the name of the player
    std::cout << "Player " << (i + 1) << " please enter your name: "; //let the player enter his name
    std::cin >> playerName; //get name input

    //create a new player
    newPlayer = new Player();
    newPlayer -> setName(playerName); //set the name of the player
    std::cout << newPlayer -> getName() << "," << " please choose your character: " << std::endl; //now the player must choose his character

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
      newPlayer -> setCharacter(static_cast<Characters>(characterChosen - 1));
      //also modify the entry in the array of already chosen characters
      chosenCharacters[i] = static_cast<Characters>(characterChosen - 1);
    }

  }

  //since we no longer need the array of chosen characters, we need to free up the memory
  delete[] chosenCharacters;
  chosenCharacters = NULL;
}

void GameSetupFunctions::setPlayerStartZones()
{
  //this is a method to set the start zones for the players based on their choice

  //we need to allow each player to set his start zone
  SinglyLinkedList<Player*>* playerList = Player::players;
  node<Player*>* curr = playerList -> getHead();

  //we will also need an array to track where each player is starting to make sure that the constraint of not
  //having more than two players per zone is not violated
  //this array should have a size equal to the number of players and should be initialized with values that are
  //impossible for the player to choose anyway, say -1, to make sure that there is no overlap

  int* playerPositions = new int[playerList -> getCount()];

  //now initialize everything to -1

  for(int i = 0; i < playerList -> getCount(); i++)
  {
    playerPositions[i] = -1;
  }

  //we will also need an int to track which player we are on
  int currPlayer = 0;

  //we need to set the zone for each player one by one
  while(curr != NULL)
  {
    //for each player, list all the zones that are available in the graph and allow him to choose the position that he wants
    //assuming that it is valid

    int vertexCount = 1; //the number that will be placed next to the vertex when giving the player the choice of his start vertex

    //now that all the vertices have been displayed, we need to allow the player to choose the vertex where he wants to start
    std::cout << curr -> getData() -> getName() << "," << " please select the location where you would like your adventure to begin: " << std::endl;

    for(int j = 0; j < MapLoader::getMap() -> getVertexCount(); j++)
    {
      //output the vertex that the player can choose from
      std::cout << vertexCount << ". " << MapLoader::getMap() -> getVertex(j) -> toString() << std::endl;
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

        if((startVertex - 1) < 1 || (startVertex - 1) > MapLoader::getMap() -> getVertexCount())
        {
          //if the chosen vertex is outside of the bounds that are acceptable, then throw an error
          vertexOutOfBounds = true; //the vertex is out of bounds
          throw startVertex;
        }

        if(MapLoader::getMap() -> getVertex(startVertex - 1) -> getData() == "master" || MapLoader::getMap() -> getVertex(startVertex - 1) -> getData() == "inner")
        {
          //if the requested vertex is a master or inner type vertex that mean it is either manhattan or one of its inner zones
          //the rules state that a player cannot start in manhattan, and therefore these zones are invalid as start zones
          vertexIsInMaster = true;
          throw startVertex;
        }

        //we should also verify if the node that the player wants to move to already has two players in it
        //compare the vertex the player wants to start at to the position of each other player
        int nbOfPlayersInStartZone = 0; //this will track the number of players in the zone where the player wants to start

        for(int i = 0; i < playerList -> getCount(); i++)
        {
          if(playerPositions[i] == (startVertex - 1))
            nbOfPlayersInStartZone++;
        }

        //if there are two or more players in that zone, then the start zone is not valid and we should throw an exception
        if(nbOfPlayersInStartZone >= 2)
          throw NodeFullException();

        //if we made it here without throwing an exception, then our location is valid

        curr -> getData() -> setZone(startVertex - 1); //set the zone to the one indicated, minus one since in our choices we start at 1
        std::cout << curr -> getData() -> getName() << ", you will begin in " << MapLoader::getMap() -> getVertex(curr -> getData() -> getZone()) -> toString() << "." << std::endl;
        playerPositions[currPlayer] = startVertex - 1;
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

      catch(NodeFullException e)
      {
        std::cout << e.what() << std::endl;
      }
    }

    //move to the next player
    curr = curr -> getNext();
    currPlayer++;
  }

  //finally make sure we clear the memory
  delete[] playerPositions;
}

void GameSetupFunctions::setMap(std::string map_directory)
{
  //the linked list that will store all the files in the given directory
  //we are using the <dirent.h> library
  DIR* d; //the pointer to the directory
  struct dirent* e; //an iterator for the directory

  int c = 1; //this will be placed before the name of the file and will allow the player to choose a map file
  int checkIter = 0; //this will check if we are passed the two first iterations, see comment below
  int fileChosen; //this will be the file that the user has chosen
  SinglyLinkedList<DirectoryFile>* fileList = new SinglyLinkedList<DirectoryFile>(); //this will hold the files in the directory for the user to choose from
  node<DirectoryFile>* toAdd; //a pointer that will be used to hold the node to add to the list of files

  //we try to open that directory
  if((d = opendir(map_directory.c_str())) != NULL)
  {
    //if the directory has been found, then we should list all of the files in that directory
    //we do this with the readdir function
    while((e = readdir(d)) != NULL)
    {
      /*
      when we show the contents of the directory there are always two elements that we don't want to show
      The first element is always "." and the second ".."
      Since we don't want to player to choose these because they mean nothing, we should simply begin showing
      when we are past two iterations
      */
      if(checkIter >= 2)
      {
        //if we are past the first two iterations, then we should display the file to the user

        //we should also add that file to a linked list that will hold all the files
        toAdd = new node<DirectoryFile>();

        //each node should hold a directory file object
        DirectoryFile fileToAdd; //the new file to add to the list
        fileToAdd.setDir(map_directory); //the directory of the file
        fileToAdd.setFile(e -> d_name); //the name of the file

        toAdd -> setData(fileToAdd); //set the data in the node to the new file
        fileList -> add(toAdd); //add that file to the list
      }

      else
      {
        //if we are not past the first two, then increment the check for the number of iterations
        checkIter++;
      }
    }
  }

  else
  {
    //if the directory was not found, then we should throw an appropriate exception
    throw DirectoryNotFoundException();
  }

  //if we got to the end and the fileList is empty, then we should throw an exception
  if(fileList -> getCount() == 0)
  {
    throw fileList -> getCount();
  }

  //close the directory since we are done
  closedir(d);

  //now we should show the list to the player
  node<DirectoryFile>* curr = fileList -> getHead();

  //we want the player to enter the number corresponding to the file that he has chosen

  bool validChoice = false;

  //we will show the list of choices and prompt the player until he has made a valid choice
  do
  {
    //ask him to choose a file from those we will show him
    //show him the name of the directory as well
    std::cout << "Maps Directory: " << map_directory << std::endl;
    std::cout << "Please select a file from the following list: " << std::endl;

    //display the contents of the directory
    while(curr != NULL)
    {
      std::cout << c << ". " << curr -> getData().getFile() << std::endl;
      curr = curr -> getNext();
      c++;
    }

    //now we should ask the player to enter his choice
    std::cout << "Please enter the number corresponding to the map you wish to play with: ";

    try
    {
      //the player enters his choice and we decide if it is valid or not
      //for the choice to be valid, we need to check if the number entered was between 1 and the count of items in the list
      std::cin >> fileChosen;

      if(fileChosen < 1 || fileChosen > fileList -> getCount())
      {
        throw fileChosen;
      }

      validChoice = true;
    }

    catch(int)
    {
      //output a message saying that the number was not valid and then start again
      std::cout << "The number " << fileChosen << " is not valid. Please try again..." << std::endl;
      validChoice = false;
    }

  } while(!validChoice);

  //now that the user has selected a valid file, we need to assign that file to the file path for the map loader
  //first we need a pointer to that directory file in the list

  //start at the first element in the list
  int k = 1;
  curr = fileList -> getHead();

  while(k < fileChosen)
  {
    k++;
    curr = curr -> getNext();
  }

  //now curr is pointing to the file we want to load

  std::cout << "The file you have chosen is: " << curr -> getData().getDir() << "\\" << curr -> getData().getFile() << std::endl;

  //now we should set the file path for the map to load
  MapLoader::setFilePath(curr -> getData().getDir() + "\\" + curr -> getData().getFile());

  //make sure the file list is cleared from memory
  delete fileList;
}

void GameSetupFunctions::setPlayerTurnOrder()
{
  /*
  This method's purpose is to set the order in which the players will take their turns
  this is done by having them roll dice, and the players having rolled more attack cubes go before the ones with less
  */
  std::cout << "The order of play will now be determined." << std::endl;

  int* attackCount = new int[Player::players -> getCount()]; //this will keep track of how many attack rolls each player has rolled
  //the player must also roll the green dice, therefore we should create a green dice object as well
  GreenDice gd;

  //let's initialize everything in the attackCount array to 0
  for(int k = 0; k < Player::players -> getCount(); k++)
  {
    attackCount[k] = 0;
  }

  //now we should go through each player and have each one roll his dice
  SinglyLinkedList<Player*>* players = Player::players;
  node<Player*>* curr = players -> getHead();
  int i = 0; //to track the position in the attack count array

  while(curr != NULL)
  {
    //for each player, we roll his dice once and we record the number of attack rolls
    //ask the player if he is ready to roll

    std::cout << curr -> getData() -> getName() << ", your turn to roll." << std::endl;
    std::cout << curr -> getData() -> getName() << ", press any key to roll the black dice." << std::endl;
    system("pause");

    std::cout << "Now rolling the dice for " << curr -> getData() -> getName() << std::endl;
    curr -> getData() -> rollDiceOnce();

    //we now need to count the number of attack rolls that this player got
    Dice* dice = curr -> getData() -> getDice();

    enum DiceFaces* result = dice -> getResult();

    //now we count the number of attack rolls for each player and we set that number in the array tracking attack rolls
    for(int j = 0; j < 6; j++)
    {
      if(result[j] == Attack)
      {
        attackCount[i]++;
      }
    }

    //we also need to roll the green dice and add the attack faces from those dice to the result
    std::cout << curr -> getData() -> getName() << ", press any key to roll the green dice." << std::endl;
    system("pause");

    gd.roll();
    std::cout << gd.toString() << std::endl;

    //the result of the green dice
    enum DiceFaces* gr = gd.getResult();

    for(int m = 0; m < 2; m++)
    {
      //we now cycle through the result of the green dice and we add to the attack count if an attack face was rolled
      if(gr[m] == Attack)
      {
        attackCount[i]++;
      }
    }

    curr = curr -> getNext();
    i++;
  }

  //now we need to determine the turn order based on the number of attack rolls each player got

  //now that we have the attack rolls stored for all the players we need to assign their turn order

  //it will be important to keep track of which players have already been assigned a position in the turn order
  //this will be stored in an array of booleans

  bool* turnSet = new bool[players -> getCount()];
  //this will hold a value indicating whether or not the player has been assigned a turn order
  //intially every element should be false;
  for(int p = 0; p < players -> getCount(); p++)
  {
    turnSet[p] = false;
  }

  //every player needs a position, therefore this process should be executed as many times as there are players

  for(int tp = 0; tp < players -> getCount(); tp++)
  {
    //now we need to go through the array attackCount and find the maximum number but only for those players that
    //still don't have their position set
    int maxAttack = -1;
    int playerWhoRolledMax = 0;

    //get the max attack rolled for the players who don't already have their turn set
    for(int loc = 0; loc < players -> getCount(); loc++)
    {
      //only consider the attack rolled if that player still doesn't have his turn set
      if(attackCount[loc] > maxAttack && !turnSet[loc])
      {
        maxAttack = attackCount[loc];
        playerWhoRolledMax = loc;
      }
    }

    //now we need to assign the turn number to the player who rolled the max
    curr = players -> getHead();

    //we need to go down the linked list until we find the player who rolled the max, namely we do loc iterations
    int pl = 0;

    //go down the list until we have done playerWhoRolledMax iterations
    while(pl != playerWhoRolledMax)
    {
      curr = curr -> getNext();
      pl++;
    }

    //now curr should be holding the node with the player who rolled the highest number
    curr -> getData() -> setPlayerNumber(tp+1);

    turnSet[playerWhoRolledMax] = true;
  }

  //to make iterating through the linked list easier in the main game loop, now that the turn order has been set
  //we should reorder the elements in the linked list



  //to do this, we will cycle through our list and sort it by player order

  //we need to go all the way down to the tail the first time in our search, then one less iteration every time
  int it = 0; //this will keep track of which iteration we are on
  node<Player*>* nodeWithMaxPlayerCount = players -> getHead(); //this is a pointer that will hold
                                                                //the node that has the max player count

  while(players -> getCount() - it > 0)
  {
    //reset the curr node to the head of the list
    curr = players -> getHead();
    while(curr != NULL)
    {
      //while going through the linked list, we are looking for the node that has a player count of
      //players -> getCount() - it

      if(curr -> getData() -> getPlayerNumber() == players -> getCount() - it)
      {
        //if we have found the node with the correct player number, point our maxplayercount node to it

        nodeWithMaxPlayerCount = curr;
      }

      curr = curr -> getNext();
    }

    //now that the node with the max player count is being pointed to, we should pull it from the list and add it
    //back at the start

    nodeWithMaxPlayerCount = players -> pull(nodeWithMaxPlayerCount);
    nodeWithMaxPlayerCount -> setNext(NULL);
    players -> add(nodeWithMaxPlayerCount);

    it++;
  }

  //now we should output the turn order:

  curr = players -> getHead();

  int ord = 1; //only used for the output message

  while(curr != NULL)
  {
    std::string playerOrder = "";
    ord = curr -> getData() -> getPlayerNumber();

    //this will be appended to the output to show where in the order of play the players will play
    switch(ord)
    {
      case 1: playerOrder = "first";
              break;
      case 2: playerOrder = "second";
              break;
      case 3: playerOrder = "third";
              break;
      case 4: playerOrder = "fourth";
              break;
      case 5: playerOrder = "fifth";
              break;
      case 6: playerOrder = "sixth";
              break;
    }

    //output the list of the turn order
    std::cout << curr -> getData() -> getName() << ", you will go " << playerOrder << "." << std::endl;
    curr = curr -> getNext();
  }

  //cleaning up the dynamic arrays
  delete[] turnSet;
  delete[] attackCount;
}
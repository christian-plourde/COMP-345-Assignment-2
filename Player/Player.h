#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Characters.h"
#include "../Lib/StringFunctions.h"
#include "CharacterMethods.h"
#include "../Dice/Dice.h" //each player should have a dice object
#include "../Graph/Graph.h"
#include "../Lib/Exceptions/MasterNodeFullException.h"
#include "../MapLoader/MapLoader.h"
#include "../Deck/CardDeck.h"
#include "../Lib/Exceptions/NotEnoughEnergyException.h"
#include "../Lib/Exceptions/NotEnoughDestructionRolledException.h"
#include "../Lib/Exceptions/MapNotLoadedException.h"
#include "../Deck/TileDeck.h"

class Player
{
  private:
    static Characters* chosenCharacters; // an array holding all the characters that have been chosen so far so that no character is played by more than one player
    static int playerCount; //the number of players that are playing the game
    int playerNumber; //player 1, player 2, etc.
    std::string name; //the name of the player
    enum Characters character; //the character that the player is playing as
    int health; //the number of health points the player has
    int energy; //the number of energy cubes the player has
    int victoryPoints; //the number of victoryPoints the player has
    int zone; //the zone that the player is currently in
    void initializeChosenCharacters(); //a method to initialize the chosen characters when beginning the game
    Dice* dice; //the dice that the player will be rolling
    SinglyLinkedList<Card>* cards; // this is a linked list holding all the cards that the player has in his hand
    //TODO add linked list of tokens

  public:
    Player(); //default constructor
    Player(std::string); //a constructor that sets the name of the player
    ~Player(); //class destructor
    std::string getName(); //a method to get the name of the player
    void setName(std::string); //a method to set the name of the player
    int getHealth(); //a method to get the health of a player
    void setHealth(int); //a method to set the health of a player
    int getVictoryPoints(); //a method to get the number of victory points a player has
    void setVictoryPoints(int); //a method to set the number of victoryPoints a player has
    void setCharacter(); //set the character that the player is playing as
    std::string toString(); //returns a string containing information about the current status of the player
    enum Characters getCharacter(); //get the character that the player is playing as
    void setCharacter(enum Characters); //set the character that the player is playing as
    static int getPlayerCount(); //get the number of players in the game
    static void setPlayerCount(int); //set the number of players in the game
    void setPlayerNumber(int); //set the number of the player: player1, player2, etc.
    int getPlayerNumber(); //get the number of the player: player1,player 2, etc.
    static enum Characters* getChosenCharacters(); //gets a pointer to an array holding the chosen characters
    int getZone(); //return the zone that the player is currently in as an array index in graph. to get the name of the zone, call a method from graph
                   //with the returned integer
    void setZone(int); //set the zone that the player should now be in.
    void setEnergy(int); //set the energy cube count for the player -- for testing only
    int getEnergy(); //return the energy that the player currently has
    Dice* getDice(); //return a pointer to the dice object that this player is using
    void rollDice(); //a method for the player to roll the dice based on the rules of the game
    void rollDiceOnce(); //a method to roll the dice only once, used to determine order of play
    void move(); //a method to allow the player to move from one region to another
    void resolveDice(); //a method to resolve the dice that the player has rolled. It should be called when the player
                        // is finished rolling his dice
    void buyCards(CardDeck*); //a method to allow the player to buy cards
    SinglyLinkedList<Card>* getCards(); //gets the list of cards the player has in his hand
    static SinglyLinkedList<Player*>* players; // a singly linked list containing a pointer to each player
	
	void removePlayer(enum Characters);
};

#endif
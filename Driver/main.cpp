#include "../Dice/Dice.h"
#include "../Player/Player.h"
#include "../MapLoader/MapLoader.h"
#include "../Lib/GameSetupFunctions.h"
/*
#include "Dice.h"
#include "Player.h"
#include "MapLoader.h"
#include "GameSetupFunctions.h"
*/
#include <iostream>
#include <string>

int main()
{
	//welcome message
	std::cout << "------------------------------" << std::endl;
	std::cout << "|      KING OF NEW YORK      |" << std::endl;
	std::cout << "|    BY CHRISTIAN PLOURDE    |" << std::endl;
	std::cout << "|       AND JACK BURNS       |" << std::endl;
	std::cout << "------------------------------" << std::endl;

	//MapLoader::loadMap("D:\\Computer Science Assignments\\COMP 345 Assignments\\A2\\Maps");
	MapLoader::loadMap();
	std::cout << MapLoader::getMap()->toString() << std::endl;

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
		catch (int e)
		{
			std::cout << "The number of players should be between 2 and 6. Please try again." << std::endl;
		}

	}

	//now that we have set the number of players playing the game it is time to initialize their player characters
	GameSetupFunctions::initializePlayers(playerCount);

	//now let's set the order in which they will play
	GameSetupFunctions::setPlayerTurnOrder();

	GameSetupFunctions::setPlayerStartZones(); //set the zones where the players will begin

	std::cout << "Ready to begin the game!" << std::endl; //ready to start!

	TileDeck* deck = new TileDeck();								// creates a deck of tiles
	node<Player*>* playerNodes = Player::players->getHead();		// list of players to go through for game loop
	Player* playerData = playerNodes->getData();					// holds data about current player
	CardDeck* cardDeck = new CardDeck();							// creates a deck of cards
	node<Player*>* curr = Player::players->getHead();				// same list of players, but used for additional traversals while inside game loop
	bool playersInManhatten = false;								// check for whether any players are in any manhatten zones
	const int WINNING_VICTORY_POINTS = 20;							// total number of victory points required for winning
	bool hasWon = false;											// flag for if any player has won

	// MAIN GAME LOOP
	// LOOP RUNS WHILE THERE ARE MORE THAN ONE PLAYERS IN THE GAME
	while (Player::players->getCount() > 1) {
		// CHECK IF ANY PLAYERS HAVE 20 VICTORY POINTS
		playerNodes = Player::players->getHead();
		while (playerNodes) {
			playerData = playerNodes->getData();
			if (playerData->getVictoryPoints() == WINNING_VICTORY_POINTS)
				hasWon = true;
			playerNodes = playerNodes->getNext();
		}
		if (hasWon)
			break;

		// NO WINNING PLAYER YET, KEEP PLAYING GAME
		playerNodes = Player::players->getHead();
		while (playerNodes) {
			playerData = playerNodes->getData();
			cout << std::endl << playerData->getName() << "'s turn" << std::endl;
			// 1. Roll the Dice (up to 3 times)
			playerData->rollDice();
			// 2. Resolve the Dice
			playerData->resolveDice();
			// CHECK IF PLAYER DIED WHILE RESOLVING THE DICE
			if (playerData->getHealth() == 0)
				break;
			// 3. Move (generally optional, sometimes mandatory)
			if (playerData) {
				// CHECK IF PLAYER IS ALREADY IN MANHATTEN
				// IF SO MOVE PLAYER UP TO NEXT ZONE
				int playerZone = playerData->getZone();
				if (playerZone == 1)
					playerData->setZone(2);
				else if (playerZone == 2)
					playerData->setZone(3);
				else if (playerZone == 4)
					playerData->setZone(5);
				else if (playerZone == 5)
					playerData->setZone(6);
				else if (playerZone != 3 || playerZone != 6) {
					// PLAYER IS NOT IN MANHATTEN
					// FIRST CHECK IF MANHATTEN HAS ANY PLAYERS IN IT
					playersInManhatten = false;
					curr = Player::players->getHead();
					while (curr) {
						playerZone = curr->getData()->getZone();
						if (playerZone <= 6) {
							playersInManhatten = true;
							break;	
						}
						curr = curr->getNext();
					}
					// IF NO PLAYERS IN MANHATTEN, MOVE PLAYER THERE
					if (!playersInManhatten) {
						std::cout << "No one in Manhatten, you must move there." << std::endl;
						if (Player::getPlayerCount() < 5)
							playerData->setZone(1);
						else
							playerData->setZone(4);
					}
					else {
						// AT LEAST ONE PLAYER IN MANHATTEN, GIVE PLAYER CHOICE AS TO WHERE TO MOVE
						bool badInput = true;
						string answer;
						std::cout << "There is already one monster in Manhatten." << std::endl;
						std::cout << "Would you like to move(M) from or stay(S) in " << MapLoader::getMap()->getVertex(playerData->getZone())->getName() << "? (M/S): ";
						while (badInput) {
							try {
								std::cin >> answer;
								if (!(answer == "M" || answer == "S")) {
									throw answer;
								}
								badInput = false;
							}
							catch (string s) {
								std::cout << "The answer " << s << " is not valid. Please enter either M or S: ";
							}
						}
						if (answer == "M")
							playerData->move();
					}

				}

				// DEAL WITH ATTACK DICE
				// PLAYER IS NOT IN MANHATTEN, ALLOW MANHATTEN PLAYERS TO MOVE OUT
				bool attack = false;
				playerZone = playerData->getZone();
				if (playerZone >= 7) {
					std::cout << "\n\nAllowing Manhatten players that were attacked to leave Manhattan\n";
					for (int i = 0; i < 6; i++) {
						if (playerData->getDice()->getResult()[i] == Attack) {
							attack = true;
							curr = Player::players->getHead();
							while (curr) {
								playerZone = curr->getData()->getZone();
								if (playerZone <= 6) {
									std::cout << "Player " << curr->getData()->getName() << " you may move\n";
									bool badInput = true;
									string answer;
									std::cout << "Would you like to move(M) from or stay(S) in " << MapLoader::getMap()->getVertex(curr->getData()->getZone())->getName() << "? (M/S): ";
									while (badInput) {
										try {
											std::cin >> answer;
											if (!(answer == "M" || answer == "S")) {
												throw answer;
											}
											badInput = false;
										}
										catch (string s) {
											std::cout << "The answer " << s << " is not valid. Please enter either M or S: ";
										}
									}
									if (answer == "M")
										curr->getData()->move();
								}
								curr = curr->getNext();
							}
						}
						if (attack)
							break;
					}
					std::cout << "\n\nBack to " << playerData->getName() << "'s turn\n";
				}


				// 4. Buy Cards (optional)
				playerData->buyCards(cardDeck);
				std::cout << std::endl << "END OF TURN, HEALTH: " << playerData->getHealth() << std::endl;
				std::cout << "VICTORY POINTS: " << playerData->getVictoryPoints() << std::endl;
				std::cout << "ZONE: " << MapLoader::getMap()->getVertex(playerData->getZone())->getName() << std::endl;
				// 5. End Turn
				// get next player
				playerNodes = playerNodes->getNext();
			}
		}
	}

	// WINNING DUE TO BEING ONLY PLAYER LEFT
	if(Player::players->getCount() == 1)
		std::cout << "CONGRATULATIONS!! " << Player::players->getHead()->getData()->getName() << " HAS WON!" << std::endl;
	else {
		// WINNING DUE TO GETTING 20 VICTORY POINTS
		// HAVE TO FIND THAT WINNER AND DISPLAY THEM
		playerNodes = Player::players->getHead();
		while (playerNodes) {
			playerData = playerNodes->getData();
			if (playerData->getVictoryPoints() == WINNING_VICTORY_POINTS) {
				std::cout << "CONGRATULATIONS!! " << playerData->getName() << " HAS WON!" << std::endl;
				break;
			}
			playerNodes = playerNodes->getNext();
		}
	}
	// CLEAN UP POINTERS
	delete[] deck;
	deck = NULL;
	delete playerNodes;
	playerNodes = NULL;
	delete playerData;
	playerData = NULL;
	delete cardDeck;
	cardDeck = NULL;
	std::system("pause");
	return 0;
}

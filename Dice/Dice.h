#ifndef DICE_H
#define DICE_H

#include "DiceFaces.h"
#include <string>

class Dice
{
  //the dice class
  private:
    enum DiceFaces* rolled; //an array of size 6 holding the result of the dice roll
    int diceToReRoll; //the number of dice to be rerolled on roll 2 or 3
    int* getDiceToRoll(); //a method to prompt the user for the dice he would like to reroll
    void setDiceToReRoll(int); //method to set the number of dice to be rerolled

  public:
    Dice(); //default constructor
    ~Dice(); //destructor
    void roll(); //method to roll the dice (all of them)
    void rollSelectedDice(); //a method to reroll dice selected by the user
    enum DiceFaces* getResult(); //method to get the result of the dice roll
    std::string toString(); //method to display the result of the roll
    int getDiceToReRoll(); //a method to get the number of dice to be rerolled

};

#endif
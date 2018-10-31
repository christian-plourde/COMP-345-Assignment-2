#ifndef GREEN_DICE_H
#define GREEN_DICE_H

#include "DiceFaces.h"
#include <string>

class GreenDice
{
  //this is class that holds the data and methods related to the two green dice in the game
  private:
    enum DiceFaces* rolled; //an array of size 2 holding the result of the roll

  public:
    GreenDice();
    ~GreenDice();
    void roll();
    enum DiceFaces* getResult();
    std::string toString();

};

#endif
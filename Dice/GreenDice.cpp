#include "GreenDice.h"
#include "../Lib/RandomNumberGenerator/RandomNumberGenerator.h"
#include "DiceFacesMethods.h"
#include <iostream>
#include <time.h>

GreenDice::GreenDice()
{
  //creates a new GreenDice object
  rolled = new enum DiceFaces[2];
  rolled[0] = Attack;
  rolled[1] = Attack;
}

GreenDice::~GreenDice()
{
  //destroyes the array of dicefaces containing the result of the last roll
  delete[] rolled;
}

void GreenDice::roll()
{
  //method to roll the green dice
  std::cout << "Rolling all the green dice..." << std::endl;

  RandomNumberGenerator* r = new RandomNumberGenerator(time(NULL)); //my random number generator, seed with the time this time, otherwise
                                                                    //sequence will be the same as regular roll
  long* randomNumbers = r -> randomGen(2,0,6);

  for(int i = 0; i<2; i++)
  {
    enum DiceFaces face = Attack; //the face of the dice

    //set the face of the dice properly
    switch(randomNumbers[i])
    {
      case 0: face = Energy;
      break;
      case 1: face = Attack;
      break;
      case 2: face = Destruction;
      break;
      case 3: face = Heal;
      break;
      case 4: face = Celebrity;
      break;
      case 5: face = Ouch;
      break;
    }

    //assign the dice face to the position in the array of roll results
    rolled[i] = face;

  }

  //now that we no longer need the random number generator we should delete its resources and also the random number array
  delete r;
  r = NULL;
  delete[] randomNumbers;
  randomNumbers = NULL;

}

enum DiceFaces* GreenDice::getResult()
{
  return rolled;
}

std::string GreenDice::toString()
{
  std::string output = "";
  output += "[";
  for(int i = 0; i<2; i++)
  {

    output += DiceFacesMethods::DiceFaceToString(rolled[i]);

    if(i != 1)
    {
       output += ",";
    }

  }

  output += "]";
  return output;
}
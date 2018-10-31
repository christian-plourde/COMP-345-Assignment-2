#include "Dice.h"
#include "../Lib/RandomNumberGenerator/RandomNumberGenerator.h"
#include "DiceFacesMethods.h"
#include <time.h>
#include <iostream>
#include <cstddef>



Dice::Dice()
{
  //creates a new Dice object
  rolled = new enum DiceFaces[6];
  rolled[0] = Attack;
  rolled[1] = Attack;
  rolled[2] = Attack;
  rolled[3] = Attack;
  rolled[4] = Attack;
  rolled[5] = Attack;
  diceToReRoll = 0;
}

Dice::~Dice()
{
  //destructor
  //delete all the values in the rolled array
  delete[] rolled;
}

void Dice::roll()
{
  //method to roll the dice.
  //we need to create a random number generator
  std::cout << "Rolling all the dice..." << std::endl;

  //we need to generate 6 random numbers
  RandomNumberGenerator* r = new RandomNumberGenerator(time(NULL)); //my random number generator, seed with the time this time, otherwise
                                                                    //sequence will be the same as regular roll
  long* randomNumbers = r -> randomGen(6,0,6);

  for(int i = 0; i<6; i++)
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

void Dice::rollSelectedDice()
{
  //a method to roll dice selected by the user

  //first we need to get the dice that we wish to reroll using our getDiceToRoll method

  int* dice = getDiceToRoll();

  //now inside dice, we have an array of integers that corresponds to the dice that we wish to reroll
  //since the indices range from 1 to 6 for user convenience, we need to make sure that when indicating which dice to reroll
  //in the rolled[] array that we subtract 1 since those indices start at 0

  //first we need to check how many dice were actually selected

  if(diceToReRoll == 0)
  {
    //if the user said he didn't want to reroll the dice, then we simply return
    //make sure to free the resources since we don't need them anymore
    delete[] dice;
    dice = NULL;
    return;
  }

  else if(diceToReRoll == 6)
  {
    //if the user said he wanted to reroll all the dice, then we call the simple roll method
    //make sure to free the resources since we don't need them anymore
    delete[] dice;
    dice = NULL;
    roll();
    return;
  }

  else
  {
    //otherwise, if he has specified the dice he wishes to roll, then we must roll the dice he said to reroll
    std::cout << "Rerolling selected dice..." << std::endl;

    //we will need to generate the right number of random numbers
    //we need to generate (diceToReRoll) random numbers

    RandomNumberGenerator* r = new RandomNumberGenerator();
    long* randomNumbers = r -> randomGen(diceToReRoll, 0, 6);

    int randomNumberIndex = 0; //this will keep track of which random number we are at in our assignment

    //now we have an array with diceToReRoll random numbers between 0 and 6 that we need to assign the right indices

    for(int j = 0; j < diceToReRoll; j++)
    {
      //for each dice in the dice array, assign the current value of the random number array to the rolled array
      rolled[dice[j] - 1] = static_cast<enum DiceFaces>(randomNumbers[randomNumberIndex]);
      randomNumberIndex++; //then increment the randomNumberIndex so that in the next iteration we take the next random number
    }

    //make sure to free the resources since we don't need them anymore
    delete[] dice;
    dice = NULL;
    delete r;
    r = NULL;
    delete[] randomNumbers;
    randomNumbers = NULL;

  }

}

int* Dice::getDiceToRoll()
{
  //this is a method to prompt the user to enter a list on numbers corresponding to the dice that he would like to roll

  //to do this, we ask the player how many dice he would like to reroll

  int input;
  bool reRollIsValid = false;

  while(!reRollIsValid)
  {
    //while the number entered is not valid, we keep prompting the user for the number of dice he wants to reroll

    std::cout << "Please enter the number of dice that you would like to reroll: ";
    std::cin >> input;

    try
    {
      setDiceToReRoll(input);
      //if we successfully set, the the reroll is valid and we can set it to true and exit the loop
      reRollIsValid = true;
    }

    catch(int e)
    {
      //if the user entered bad data, we send him a message and retry the process
      std::cout << "Please enter a number between 0 and 6." << std::endl;
    }
  }

  //now that we know how many dice he wants ro reroll, we should prompt him to enter the dice that he wishes to reroll, unless the number
  //is 6, in which case, we simply return null, the method to roll specific dice will need to look at the number of dice to be rerolled
  //to determine what should be done

  if(diceToReRoll == 0 || diceToReRoll == 6)
  {
    //if we want to reroll no dice or all of them, either way we don't need to know which ones should be rerolled so we
    //can simply return null
    return NULL;
  }

  else
  {
    //if the number requested was between 1 and 5, then we need to know which ones the user would like to reroll
    int* dice = new int[diceToReRoll]; //the thing that will be returned, containing which dice should be rerolled
    int* alreadyChosen = new int[diceToReRoll]; //we need to make sure that the same dice is not chosen twice because this is cheating!

    //initialize the alreadyChosen array to values that are out of range
    for(int j = 0; j<diceToReRoll; j++)
    {
      alreadyChosen[j] = 7;
    }

    for(int i = 0; i < diceToReRoll; i++)
    {
      //for each element in the array, i.e. the dice to reroll, we need to know which dice should be rerolled

      //once again we need to make sure that the number entered is valid

      reRollIsValid = false;

      while(!reRollIsValid)
      {
        //while the number entered is not valid, we keep prompting the user for the number of the dice he wants to reroll

        std::cout << "Please enter the number corresponding to dice number " << (i+1) << " to be rerolled: ";
        std::cin >> input;

        try
        {
          if(input < 1 || input > 6)
          {
            //if the number entered is out of range, then throw an exception
            throw input;
          }

          for(int k = 0; k<diceToReRoll; k++)
          {
            //for each dice in the already chosen array, we need to check if the value entered is equal to it.
            //if it is, then this number is invalid and we should throw an exception

            if(alreadyChosen[k] == input)
            {
              throw input;
            }
          }


          //if the number was valid, then make the number at the corresponding index equal to the input
          dice[i] = input;
          //also, we need to place it in the already chosen array
          alreadyChosen[i] = input;
          reRollIsValid = true;
        }

        catch(int e)
        {
          //if the user entered bad data, we send him a message and retry the process
          if(input < 1 || input > 6)
          {
            //if the value was out of range
            std::cout << "Please enter a number between 1 and 6." << std::endl;
          }

          else
          {
            //otherwise, this means the value was already chosen
            std::cout << "This value was already chosen!" << std::endl;
          }

        }
      }

    }


    //since the alreadyChosen array was temporary, we should free the resources
    delete[] alreadyChosen;
    alreadyChosen = NULL;
    return dice;
  }

}

enum DiceFaces* Dice::getResult()
{
  //this method returns the result of the last roll
  return rolled;
}

std::string Dice::toString()
{
  std::string output = "";
  output += "[";
  for(int i = 0; i<6; i++)
  {

    output += DiceFacesMethods::DiceFaceToString(rolled[i]);

    if(i != 5)
    {
       output += ",";
    }

  }

  output += "]";
  return output;
}

void Dice::setDiceToReRoll(int num)
{
  //this sets the amount of dice to be rerolled
  if(num < 0 || num > 6)
  {
    throw num; //if the number is invalid, i.e roll more dice than we have or a negative number, then throw an exception
  }

  else
  {
    diceToReRoll = num;
  }
}

int Dice::getDiceToReRoll()
{
  return diceToReRoll;
}

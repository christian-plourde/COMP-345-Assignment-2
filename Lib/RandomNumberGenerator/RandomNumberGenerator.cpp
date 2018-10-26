#include "RandomNumberGenerator.h"
#include <iostream>
#include <time.h>

long long RandomNumberGenerator::MULTIPLIER = 1664525;
long long RandomNumberGenerator::CONSTANT = 1013904223;
long long RandomNumberGenerator::MODULUS = power(2,32);

RandomNumberGenerator::RandomNumberGenerator()
{
  //the default constructor sets the seed to the time
}

RandomNumberGenerator::RandomNumberGenerator(long long seed)
{
  //sets the seed to user defined value
  this -> seed = seed;
}

RandomNumberGenerator::~RandomNumberGenerator()
{
  //class destructor
}

void RandomNumberGenerator::setSeed(long long seed)
{
  this -> seed = seed;
}

long* RandomNumberGenerator::randomGen(int size)
{
  //this function returns a pointer to an array of long random numbers of the size specified by the user
  long* numbers = new long[size];

  for(int i = 0; i < size; i++)
  {
    //for each number we want, change the value with the linear congruential generator
    seed = (MULTIPLIER*seed + CONSTANT)%MODULUS; //the linear congruential equation
    numbers[i] = seed; //assign the new number to the array
  }

  return numbers;
}

long* RandomNumberGenerator::randomGen(int size, int min, int max)
{
  //same as before, but this time the solution set is bounded
  //it will generate positive numbers between min and max

  long* numbers = new long[size];

  for(int i = 0; i< size; i++)
  {
    seed = (MULTIPLIER*seed + CONSTANT)%MODULUS; //the linear congruential equation

    //if the results is negative, multiply by -1
    if(seed%max + min < 0)
    {
      numbers[i] = -1*(seed%max + min);
    }

    //otherwise leave it as is
    else
    {
      numbers[i] = seed%max + min; //bounding the solution
    }

  }

  return numbers;
}

long long RandomNumberGenerator::power(int base, int exponent)
{
  //function to return the power of the base to the exponent using recursion
  //base case
  if(exponent == 0)
  {
    return 1;
  }

  //recursive case
  //each time reduce the exponent by 1 until we reach the base case and mutiply results
  else
  {
    return base*power(base, exponent - 1);
  }
}


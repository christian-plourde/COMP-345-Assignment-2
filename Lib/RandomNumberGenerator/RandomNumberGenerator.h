//this is the definition for a random number generator class that will be used in the dice rolling facility
#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

class RandomNumberGenerator
{
  //the random number generator class
  //based on a linear congruential PRNG that I originally created in java

  private:
    long long seed; //the seed for the random number generator
    static long long MULTIPLIER; //the multiplier for the PRNG
    static long long CONSTANT; //the constant for the PRNG
    static long long MODULUS; //the modulus for the PRNG
    static long long power(int,int); //this returns the power of a base to an exponent

  public:
    RandomNumberGenerator(); //default constructor
    RandomNumberGenerator(long long); //constructor that accepts an initial seed value
    ~RandomNumberGenerator(); //destructor
    void setSeed(long long); //set the seed of the PRNG
    long* randomGen(int); //creates an array of long random numbers of the size specified
    long* randomGen(int,int,int); //creates an array of long random numbers of size specified between two bounds
};

#endif
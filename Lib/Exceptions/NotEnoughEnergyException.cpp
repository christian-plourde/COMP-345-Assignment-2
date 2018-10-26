#include "NotEnoughEnergyException.h"

//a method to return an error message for when a player wants to move to manhattan
const char * NotEnoughEnergyException::what() const throw()
{
  return "Not enough energy.";
}
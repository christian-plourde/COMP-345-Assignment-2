#include "NotEnoughDestructionRolledException.h"

//a method to return an error message for when a player wants to move to manhattan
const char * NotEnoughDestructionRolledException::what() const throw()
{
  return "You did not roll enough destruction to destroy this building.";
}
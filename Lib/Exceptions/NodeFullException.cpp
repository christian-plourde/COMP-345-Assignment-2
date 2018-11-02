#include "NodeFullException.h"

//a method to return an error message for when a player wants to move to manhattan
const char * NodeFullException::what() const throw()
{
  return "There are already two players in this zone.";
}
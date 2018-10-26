#include "MasterNodeFullException.h"

//a method to return an error message for when a player wants to move to manhattan
const char * MasterNodeFullException::what() const throw()
{
  return "Master node was full.";
}


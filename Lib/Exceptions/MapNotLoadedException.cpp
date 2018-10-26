#include "MapNotLoadedException.h"

//a method to return an error message for when a player wants to move to manhattan
const char * MapNotLoadedException::what() const throw()
{
  return "Map was not loaded yet.";
}
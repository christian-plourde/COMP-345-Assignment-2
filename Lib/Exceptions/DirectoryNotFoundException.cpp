#include "DirectoryNotFoundException.h"

//a method to return an error message for when a player wants to move to manhattan
const char * DirectoryNotFoundException::what() const throw()
{
  return "The directory does not exist.";
}
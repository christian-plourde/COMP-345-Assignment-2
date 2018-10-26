#ifndef NOT_ENOUGH_DESTRUCTION_ROLLED_EXCEPTION_H
#define NOT_ENOUGH_DESTRUCTION_ROLLED_EXCEPTION_H

#include <exception>

//an exception thrown if the map has not been loaded yet
//this can happen when resolving dice, setting tiles, etc.
struct NotEnoughDestructionRolledException
{
  //returns an error message
  const char * what() const throw();
};

#endif
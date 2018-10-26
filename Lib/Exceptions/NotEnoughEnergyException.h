#ifndef NOT_ENOUGH_ENERGY_EXCEPTION_H
#define NOT_ENOUGH_ENERGY_EXCEPTION_H

#include <exception>

//an exception thrown if the map has not been loaded yet
//this can happen when resolving dice, setting tiles, etc.
struct NotEnoughEnergyException
{
  //returns an error message
  const char * what() const throw();
};

#endif
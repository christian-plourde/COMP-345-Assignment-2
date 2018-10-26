#ifndef MAP_NOT_LOADED_EXCEPTION_H
#define MAP_NOT_LOADED_EXCEPTION_H

#include <exception>

//an exception thrown if the map has not been loaded yet
//this can happen when resolving dice, setting tiles, etc.
struct MapNotLoadedException
{
  //returns an error message
  const char * what() const throw();
};

#endif
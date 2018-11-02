#ifndef NODE_FULL_EXCEPTION_H
#define NODE_FULL_EXCEPTION_H

#include <exception>

//an exception thrown when the player wants to move to a node that already has 2 players in it
struct NodeFullException
{
  //returns an error message
  const char * what() const throw();
};

#endif
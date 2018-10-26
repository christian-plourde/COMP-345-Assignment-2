#ifndef MASTER_NODE_FULL_EXCEPTION_H
#define MASTER_NODE_FULL_EXCEPTION_H

#include <exception>

//an exception thrown when the player wants to move to manhattan
struct MasterNodeFullException
{
  //returns an error message
  const char * what() const throw();
};

#endif
#ifndef DIRECTORY_NOT_FOUND_EXCEPTION_H
#define DIRECTORY_NOT_FOUND_EXCEPTION_H

#include <exception>

//an exception thrown if the directory was not found
//this can happen when loading a map
struct DirectoryNotFoundException
{
  //returns an error message
  const char * what() const throw();
};

#endif
#include "DirectoryFile.h"
#include <iostream>

DirectoryFile::DirectoryFile()
{
  //default constructor will set both file and directory paths to empty strings
  dir = "";
  file = "";
}

DirectoryFile::~DirectoryFile()
{
  //destructor
}

std::string DirectoryFile::getDir()
{
  return dir;
}

std::string DirectoryFile::getFile()
{
  return file;
}

void DirectoryFile::setDir(std::string d)
{
  dir = d;
}

void DirectoryFile::setFile(std::string f)
{
  file = f;
}

std::ostream& operator << (std::ostream& os, const DirectoryFile* df)
{
  os << df -> dir << df -> file << std::endl;
  return os;
}

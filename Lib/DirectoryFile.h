//this class holds information about a file in a directory
#ifndef DIRECTORY_FILE_H
#define DIRECTORY_FILE_H

#include <string>
#include <iostream>

class DirectoryFile
{
  private:
    std::string dir; //the name of the directory
    std::string file; //the name of the file in the directory

  public:
    DirectoryFile(); //a default constructor
    ~DirectoryFile(); //a destructor
    std::string getDir(); //get the name of the directory
    std::string getFile(); //get the name of the file
    void setDir(std::string); //set the name of the directory
    void setFile(std::string); //set the name of the file
    friend std::ostream& operator << (std::ostream&, const DirectoryFile*); //operator overload for printing to console
};



#endif
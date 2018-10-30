#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "../Graph/Graph.h"
#include <string>

//this header file contains the definition for the map loader class, which provides methods for loading map files
//into the game and outputs a graph that contains the data in the map file

class MapLoader
{
  public:
    static void loadMap(); //loads a .map file from a directory into the static graph field of the class
    static void setFilePath(std::string);
    static std::string getFilePath();
    static Graph<std::string>* getMap(); //get the graph containing the game board

  private:
    static bool fileIsValid(); //check if the file at the passed file path is valid or not
    static int nodeCount; //this is required for creating the graph as we need to know how many nodes are in it
    static std::string filePath; //the file path
    static Graph<std::string>* map; //the game map
};

#endif
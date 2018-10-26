#ifndef DICE_FACES_METHODS_H
#define DICE_FACES_METHODS_H

#include "DiceFaces.h"
#include <string>

namespace DiceFacesMethods
{
  std::string DiceFaceToString(enum DiceFaces face)
  {
    std::string output = "";
    switch(face)
    {
      case Energy: output += "Energy";
      break;
      case Attack: output += "Attack";
      break;
      case Destruction: output += "Destruction";
      break;
      case Heal: output += "Heal";
      break;
      case Celebrity: output += "Celebrity";
      break;
      case Ouch: output += "Ouch";
      break;
    }

    return output;
  }
}

#endif
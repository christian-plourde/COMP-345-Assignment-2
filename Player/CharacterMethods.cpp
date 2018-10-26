#include <string>
#include "CharacterMethods.h"

std::string CharacterMethods::characterToString(enum Characters character)
{
  std::string output = "";
  switch(character)
  {
    case CaptainFish: output = "Captain Fish";
    break;
    case Sheriff: output = "Sheriff";
    break;
    case Mantis: output = "Mantis";
    break;
    case Rob: output = "Rob";
    break;
    case Drakonis: output = "Drakonis";
    break;
    case Kong: output = "Kong";
    break;
    default: output = "";
  }

  return output;
}
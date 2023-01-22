#include "ships.h"

namespace std
{
  ostream &operator<<(ostream &out, const Ship &ship)
  {
    switch (ship)
    {
    case Ship::battle_ship:
      out << "Battleship";
      break;
    case Ship::heavy_fighter:
      out << "Heavy Fighter";
      break;
    case Ship::large_transporter:
      out << "Large Transporter";
      break;
    case Ship::light_fighter:
      out << "Light Fighter";
      break;
    case Ship::mothership:
      out << "Mothership";
      break;
    case Ship::small_transporter:
      out << "Small Transporter";
      break;
    }

    return out;
  }
}
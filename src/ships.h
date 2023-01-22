#pragma once

#include <cstdint>
#include <iostream>
#include <map>

enum class Ship
{
  light_fighter,
  heavy_fighter,
  small_transporter,
  large_transporter,
  battle_ship,
  mothership,
};

using Fleet = std::map<Ship, uint32_t>;

namespace std
{
  ostream &operator<<(ostream &out, const Ship &ship);
}
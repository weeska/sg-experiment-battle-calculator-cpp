#pragma once

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "ships.h"

struct FightableSpecs
{
  uint32_t hull;
  uint32_t shields;
  uint32_t weapons;
};

using FleetWithSpecs = std::map<Ship, std::vector<FightableSpecs>>;

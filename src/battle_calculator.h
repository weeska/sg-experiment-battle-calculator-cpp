#pragma once

#include <string>

#include "ships.h"
#include "fightable.h"

struct Opponents {
  Fleet attacker;
  Fleet defender;
};

struct BattleRound : public Opponents {
    uint8_t round;
};

struct BattleResult
{
  std::string winner;
  Opponents start;
  std::vector<BattleRound> rounds;
};

FightableSpecs shipSpecs(Ship ship);
FleetWithSpecs toFleetSpecs(const Fleet &fleet);
Fleet toFleet(const FleetWithSpecs &fleet);

void fight(const FightableSpecs &attacker, FightableSpecs &target, const FightableSpecs &reference);
void destroy_ship(std::vector<FightableSpecs> &specs, size_t index);
void doBattle(const FleetWithSpecs &attackerSpecs, FleetWithSpecs &defenderSpecs);
bool isFleetEmpty(const FleetWithSpecs &fleet);

class BattleCalculator
{
public:
  BattleResult calculate(const Fleet &attacker, const Fleet &defender) const;

  void resetShields(FleetWithSpecs &fleet) const;
private:
  std::vector<FightableSpecs> toArray(Ship ship, uint32_t count) const;
  std::string getResult(const FleetWithSpecs &attacker, const FleetWithSpecs &defender) const;
};
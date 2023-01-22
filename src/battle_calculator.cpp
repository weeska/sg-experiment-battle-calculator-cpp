#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <vector>

#include "battle_calculator.h"

void destroy_ship(std::vector<FightableSpecs> &specs, size_t index)
{
  specs[index] = specs[specs.size() - 1];
  specs.pop_back();
}

void fight(const FightableSpecs &attacker, FightableSpecs &target, const FightableSpecs &reference)
{
  if ((attacker.weapons * 100) < target.shields)
  {
    // Do nothing
  }
  else if (attacker.weapons < target.shields)
  {
    target.shields -= attacker.weapons;
  }
  else
  {
    const auto damage = (attacker.weapons - target.shields);
    target.hull = damage > target.hull ? 0 : target.hull - damage;
    target.shields = 0;
  }

  if (target.hull != 0 && (target.hull * 100) < (reference.hull * 70))
  {
    const auto prob = (1 - target.hull / reference.hull) * 100;
    const auto rand = static_cast<uint32_t>(std::rand() % 100);
    if (rand < prob)
    {
      target.hull = 0;
    }
  }
}

BattleResult BattleCalculator::calculate(const Fleet &attacker, const Fleet &defender) const
{
  static const auto maxRounds = 6;

  BattleResult result;
  result.winner = "None";
  result.start.attacker = attacker;
  result.start.defender = defender;

  auto attackerSpecs = toFleetSpecs(attacker);
  auto defenderSpecs = toFleetSpecs(defender);

  auto round = 1;

  while (!isFleetEmpty(attackerSpecs) && !isFleetEmpty(defenderSpecs) && round <= maxRounds)
  {
    doBattle(attackerSpecs, defenderSpecs);
    doBattle(defenderSpecs, attackerSpecs);

    BattleRound r;
    r.round = round;
    r.attacker = toFleet(attackerSpecs);
    r.defender = toFleet(defenderSpecs);

    result.rounds.push_back(r);

    this->resetShields(attackerSpecs);
    this->resetShields(defenderSpecs);

    round++;
  }

  result.winner = getResult(attackerSpecs, defenderSpecs);
  return result;
}

FleetWithSpecs toFleetSpecs(const Fleet &fleet)
{
  FleetWithSpecs result;

  for (const auto &shipAndAmount : fleet)
  {
    result[shipAndAmount.first] = std::vector<FightableSpecs>(shipAndAmount.second, shipSpecs(shipAndAmount.first));
  }

  return result;
}

Fleet toFleet(const FleetWithSpecs &fleet)
{
  Fleet result;

  for (const auto &shipAndAmount : fleet)
  {
    result[shipAndAmount.first] = shipAndAmount.second.size();
  }

  return result;
}

FightableSpecs shipSpecs(Ship ship)
{
  switch (ship)
  {
  case Ship::battle_ship:
    return {10000, 5000, 2500};
  case Ship::light_fighter:
    return {750, 100, 1000};
  case Ship::heavy_fighter:
    return {1000, 250, 1500};
  case Ship::small_transporter:
    return {750, 250, 100};
  case Ship::large_transporter:
    return {2000, 1500, 200};
  case Ship::mothership:
    return {2000000, 250000, 100000};
  default:
    break;
  }

  throw new std::runtime_error("");
}

bool isFleetEmpty(const FleetWithSpecs &fleet)
{
  return !std::any_of(fleet.cbegin(), fleet.cend(), [](const auto &pair)
                      { return !pair.second.empty(); });
}

void doBattle(const FleetWithSpecs &attackerSpecs, FleetWithSpecs &defenderSpecs)
{
  for (const auto &pair : attackerSpecs)
  {
    for (const auto &attacker : pair.second)
    {
      auto targetTypeIter = defenderSpecs.begin();
      if(targetTypeIter == defenderSpecs.end()) {
        return;
      }

      std::advance(targetTypeIter, rand() % defenderSpecs.size());

      auto &defendersOfType = targetTypeIter->second;
      if (!defendersOfType.empty())
      {
        const auto index = rand() % defendersOfType.size();
        auto defender = defendersOfType[index];

        fight(attacker, defender, shipSpecs(targetTypeIter->first));

        if (defender.hull == 0 && defendersOfType.size() > 0)
        {
          const auto &last = defendersOfType[defendersOfType.size() - 1];

          defender.hull = last.hull;
          defender.shields = last.shields;
          defender.weapons = last.weapons;

          defendersOfType.pop_back();
        }
      }
      else
      {
        defenderSpecs.erase(targetTypeIter);
      }
    }
  }
}

std::string BattleCalculator::getResult(const FleetWithSpecs &attacker, const FleetWithSpecs &defender) const
{
  const auto attackerFleetEmpty = isFleetEmpty(attacker);
  const auto defenderFleetEmpty = isFleetEmpty(defender);

  if (!attackerFleetEmpty && !defenderFleetEmpty)
  {
    return "draw";
  }

  if (attackerFleetEmpty)
  {
    return "defender";
  }

  return "attacker";
}

void BattleCalculator::resetShields(FleetWithSpecs &fleet) const
{
  for (auto &ship : fleet)
  {
    const auto &base = shipSpecs(ship.first);
    for (auto &spec : ship.second)
    {
      spec.shields = base.shields;
    }
  }
}

#include <iostream>

#include <benchmark/benchmark.h>

#include "battle_calculator.h"

static void shipSpecs(benchmark::State &state)
{
    for (auto _ : state)
    {
        shipSpecs(Ship::battle_ship);
    }
}

static void fleetSpecs(benchmark::State &state)
{
    for (auto _ : state)
    {
        toFleetSpecs({{Ship::battle_ship, 10000}});
    }
}

static void resetShields(benchmark::State &state)
{
    const BattleCalculator calc;
    auto specs = toFleetSpecs({{Ship::battle_ship, 10000}});

    for (auto _ : state)
    {
        calc.resetShields(specs);
    }
}

static void fight(benchmark::State &state)
{
    const FightableSpecs attacker{
        1,
        1,
        115,
    };

    FightableSpecs defender{
        120,
        100,
        1,
    };

    FightableSpecs reference{
        120,
        100,
        1,
    };

    for (auto _ : state)
    {
        fight(attacker, defender, reference);
    }
}

static void largeBattle(benchmark::State &state)
{
    const BattleCalculator calc;

    const Fleet attacker({
        {Ship::heavy_fighter, 1000000u},
        {Ship::light_fighter, 1000000u},
    });

    const Fleet defender({
        {Ship::heavy_fighter, 1000000u},
        {Ship::light_fighter, 1000000u},
    });

    for (auto _ : state)
    {
        calc.calculate(attacker, defender);
    }
}

static void doBattle(benchmark::State &state)
{
    const Fleet attacker({
        {Ship::heavy_fighter, 1000000u},
        {Ship::light_fighter, 1000000u},
    });

    const Fleet defender({
        {Ship::heavy_fighter, 1000000u},
        {Ship::light_fighter, 1000000u},
    });

    const auto attackerSpecs = toFleetSpecs(attacker);
    auto defenderSpecs = toFleetSpecs(defender);

    for (auto _ : state)
    {
        doBattle(attackerSpecs, defenderSpecs);
    }
}


BENCHMARK(shipSpecs);
BENCHMARK(fleetSpecs);
BENCHMARK(resetShields);
BENCHMARK(fight);
BENCHMARK(largeBattle);
BENCHMARK(doBattle);

BENCHMARK_MAIN();
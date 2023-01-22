#include <algorithm>
#include <chrono>
#include <iostream>
#include <map>
#include <vector>

#include "battle_calculator.h"
#include "ships.h"

int main()
{
    const Fleet attacker({
        {Ship::heavy_fighter, 1000000},
        {Ship::light_fighter, 1000000},
    });

    const Fleet defender({
        {Ship::heavy_fighter, 1000000},
        {Ship::light_fighter, 1000000},
    });

    const BattleCalculator calculator;

    const auto start = std::chrono::high_resolution_clock::now();
    const auto r = calculator.calculate(attacker, defender);
    std::cout << r.rounds.size() << std::endl;
    const auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms" << std::endl;

    for (const auto &r : r.rounds)
    {
        std::cout << "Attacker:" << std::endl;

        for (const auto &pair : r.attacker)
        {
            std::cout << "\t" << pair.first << ": " << pair.second << std::endl;
        }

        std::cout << "Defender:" << std::endl;

        for (const auto &pair : r.defender)
        {
            std::cout << "\t" << pair.first << ": " << pair.second << std::endl;
        }

        std::cout << std::endl;
    }
}

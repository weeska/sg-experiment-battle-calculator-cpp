#include <gtest/gtest.h>

#include "battle_calculator.h"

TEST(BattleCalculator, IsFleetEmpty)
{
    ASSERT_TRUE(isFleetEmpty({}));
    ASSERT_TRUE(isFleetEmpty(
        {
            { Ship::battle_ship, {} }
        }
    ));

    ASSERT_FALSE(isFleetEmpty(
        {
            { Ship::battle_ship, {
                { 1, 2, 3}
            } }
        }
    ));
}

TEST(BattleCalculator, ShieldsAbsorbWeapons)
{
    const FightableSpecs attacker{
        1,
        1,
        9,
    };

    FightableSpecs defender{
        1,
        1000,
        1,
    };

    fight(attacker, defender, defender);

    ASSERT_EQ(defender.shields, 1000);
}

TEST(BattleCalculator, ShieldsAbsorbPartialWeaponsDamage)
{
    const FightableSpecs attacker{
        1,
        1,
        15,
    };

    FightableSpecs defender{
        1,
        100,
        1,
    };

    fight(attacker, defender, defender);

    ASSERT_EQ(defender.shields, 85);
}

TEST(BattleCalculator, WeaponsExhaustShieldsAndDamageHull)
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

    fight(attacker, defender, defender);

    ASSERT_EQ(defender.shields, 0);
    ASSERT_EQ(defender.hull, 105);
}

TEST(BattleCalculator, AttackerWins)
{
    const Fleet attacker({
        {Ship::light_fighter, 1},
    });

    const Fleet defender({
        {Ship::small_transporter, 1},
    });

    BattleCalculator calc;

    const auto result = calc.calculate(attacker, defender);
    ASSERT_EQ(result.winner, "attacker");
}

TEST(BattleCalculator, DefenderWins)
{
    const Fleet attacker({
        {Ship::small_transporter, 1},
    });

    const Fleet defender({
        {Ship::light_fighter, 1},
    });

    BattleCalculator calc;

    const auto result = calc.calculate(attacker, defender);
    ASSERT_EQ(result.winner, "defender");
}

TEST(BattleCalculator, Draw)
{
    const Fleet attacker({
        {Ship::small_transporter, 100},
    });

    const Fleet defender({
        {Ship::small_transporter, 100},
    });

    BattleCalculator calc;

    const auto result = calc.calculate(attacker, defender);
    ASSERT_EQ(result.winner, "draw");
}

TEST(BattleCalculator, LargeBattle)
{
    const Fleet attacker({
        {Ship::heavy_fighter, 1000000u},
        {Ship::light_fighter, 1000000u},
    });

    const Fleet defender({
        {Ship::heavy_fighter, 1000000u},
        {Ship::light_fighter, 1000000u},
    });

    BattleCalculator calc;

    const auto result = calc.calculate(attacker, defender);
    ASSERT_EQ(result.rounds.size(), 2);
    ASSERT_EQ(result.winner, "attacker");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
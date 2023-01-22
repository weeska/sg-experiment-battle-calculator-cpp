project('battle-calc', 'cpp', default_options : ['cpp_std=c++17', 'buildtype=release'])

gtest = dependency('gtest')
gbench = dependency('benchmark')

sources = files(
    'src/battle_calculator.cpp',
    'src/ships.cpp',
)
sgbclib = library('sgbclib', sources)

executable(
    'battle-calc',
    'src/main.cpp',
    link_with: sgbclib
)

executable(
    'battle-calc-tests',
    'src/tests.cpp',
    dependencies: gtest,
    link_with: sgbclib
)

executable(
    'battle-calc-bench',
    'src/bench.cpp',
    dependencies: gbench,
    link_with: sgbclib
)

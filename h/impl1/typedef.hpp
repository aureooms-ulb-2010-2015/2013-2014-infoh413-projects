
#include <cstdint>
#include <vector>
#include <random>
#include <chrono>

#include "lib/random/sample.hpp"


typedef int SIZE_T;
typedef std::vector<SIZE_T> solution;

typedef std::default_random_engine random_engine;
typedef std::uniform_int_distribution<SIZE_T> uniform_distribution;

auto sample = lib::random::sample<random_engine, uniform_distribution, solution, SIZE_T>;

typedef std::chrono::system_clock sysclock;
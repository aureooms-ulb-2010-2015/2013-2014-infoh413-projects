
#include <cstdint>
#include <vector>
#include <random>
#include <chrono>

#include "lib/random/sample.hpp"


typedef int addr_t;
typedef long int val_t;
typedef long int priority_t;

typedef std::vector<addr_t> solution;

typedef std::default_random_engine random_engine;
typedef std::uniform_int_distribution<addr_t> uniform_distribution;

auto sample = lib::random::sample<random_engine, uniform_distribution, solution, addr_t>;

typedef std::chrono::system_clock sysclock;
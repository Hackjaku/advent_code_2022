#include <regex>
#include <fstream>
#include <iostream>

static uint32_t const ORE = 1 << 0;
static uint32_t const CLY = 1 << 8;
static uint32_t const OBS = 1 << 16;
static uint32_t const GEO = 1 << 24;

static inline uint32_t const ore(uint32_t data) { return (data >> 0) & 0xff; }
static inline uint32_t const cly(uint32_t data) { return (data >> 8) & 0xff; }
static inline uint32_t const obs(uint32_t data) { return (data >> 16) & 0xff; }
static inline uint32_t const geo(uint32_t data) { return (data >> 24) & 0xff; }

static inline uint32_t const eta(uint32_t needed, uint32_t produced) { return (needed + produced - 1) / produced; }

static uint32_t explore(uint32_t const *costs, uint32_t t, uint32_t stash = 0x0, uint32_t robots = ORE)
{
    // Default score if we just do nothing
    uint32_t best = geo(stash + t * robots);

    // Try to build an ore robot (useless if we already produce enough for any kind of robot)
    if (ore(robots) < costs[2] || ore(robots) < costs[3] || ore(robots) < costs[5])
    {
        uint32_t dt = 1 + (ore(stash) > costs[1] ? 0 : eta(costs[1] - ore(stash), ore(robots)));
        if (t > dt)
            best = std::max(best, explore(costs, t - dt, stash + dt * robots - costs[1] * ORE, robots + ORE));
    }

    // Try to build a clay robot (useless if we already produce enough for an obsidian robot)
    if (cly(robots) < costs[4])
    {
        uint32_t dt = 1 + (ore(stash) > costs[2] ? 0 : eta(costs[2] - ore(stash), ore(robots)));
        if (t > dt)
            best = std::max(best, explore(costs, t - dt, stash + dt * robots - costs[2] * ORE, robots + CLY));
    }

    // Try to build an obsidian robot (impossible if we don’t have a clay robot)
    if (cly(robots))
    {
        uint32_t dt = 1 + std::max(ore(stash) > costs[3] ? 0 : eta(costs[3] - ore(stash), ore(robots)),
                                cly(stash) > costs[4] ? 0 : eta(costs[4] - cly(stash), cly(robots)));
        if (t > dt)
            best = std::max(best, explore(costs, t - dt, stash + dt * robots - costs[3] * ORE - costs[4] * CLY, robots + OBS));
    }

    // Try to build a geode robot (impossible if we don’t have an obsidian robot)
    if (obs(robots))
    {
        uint32_t dt = 1 + std::max(ore(stash) > costs[5] ? 0 : eta(costs[5] - ore(stash), ore(robots)),
                                obs(stash) > costs[6] ? 0 : eta(costs[6] - obs(stash), obs(robots)));
        if (t > dt)
            best = std::max(best, explore(costs, t - dt, stash + dt * robots - costs[5] * ORE - costs[6] * OBS, robots + GEO));
    }

    return best;
}

int main(void)
{
    std::vector<uint32_t> data;

    std::ifstream t("../inputs/19.txt");
    std::string input((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    std::regex const r("([0-9]+)");
    std::sregex_iterator matches(input.begin(), input.end(), r), end;
    for (auto it = matches; it != end; ++it)
        data.push_back(std::atoi((*it).str().c_str()));

    uint32_t p1 = 0;
    for (size_t i = 0; i < data.size(); i += 7)
        p1 += data[i] * explore(&data.at(i), 24);
    std::cout << p1 << '\n';

    uint32_t p2 = 1;
    for (size_t i = 0; i < 3 * 7; i += 7)
        p2 *= explore(&data.at(i), 32);
    std::cout << p2 << '\n';
}
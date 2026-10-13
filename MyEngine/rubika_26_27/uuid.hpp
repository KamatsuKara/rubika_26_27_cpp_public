#pragma once
// Source - https://stackoverflow.com/a/60198074
// Posted by happy_sisyphus, modified by community. See post 'Timeline' for change history
// Retrieved 2026-10-12, License - CC BY-SA 4.0

#include <random>
#include <sstream>

namespace uuid {
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::string generate_uuid();
}

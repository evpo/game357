#pragma once
#include <vector>
#include <tuple>
#include "game_state.h"

namespace Game357
{
    using State2003 = std::vector<char>;
    State2003 ConvertTo2003(GameState &game_state);
    std::tuple<CellStatesIt, CellStatesIt> FindNewMove(GameState &game_state,
            const State2003 &after);
}

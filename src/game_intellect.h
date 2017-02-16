#pragma once
#include <tuple>
#include "game_state.h"

namespace Game357
{
    std::tuple<CellStatesIt, CellStatesIt> FindBestMove(GameState &game_state);
}

#include "game_state.h"
#include <algorithm>
#include "assert.h"

namespace Game357
{
    std::vector<CellStates> &GetGameState()
    {
        static std::vector<CellStates> game_state(15, CellStates::Open);
        return game_state;
    }

    void MakeMove(CellStatesIt begin, CellStatesIt end)
    {
        std::for_each(begin, end, [](CellStates &state){assert(state == CellStates::Open);});
        std::fill(begin, end, CellStates::Set);
    }
}

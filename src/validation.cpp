#include "validation.h"
#include <algorithm>
#include "assert.h"

namespace Game357
{
    bool IsMoveValid(GameState &state, CellStatesIt begin, CellStatesIt end)
    {
        size_t begin_index = begin - state.begin();
        size_t end_index = end - state.begin();
        if(end_index > 15U)
            return false;

        if(end_index == begin_index)
            return false;

        if(end_index - 1 < begin_index)
            return false;

        if(end_index > 3U && end_index <= 8U && begin_index < 3U)
            return false;

        if(end_index > 8U && begin_index < 8U)
            return false;

        if(std::count(begin, end, CellStates::Set) > 0)
            return false;

        return true;
    }
}

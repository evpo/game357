#pragma once
#include <vector>

namespace Game357
{
    enum class CellStates
    {
        Open, // Can be set
        Set // Set in previous moves
    };

    using GameState = std::vector<CellStates>;
    using CellStatesIt = GameState::iterator;

    GameState &GetGameState();

    void MakeMove(CellStatesIt begin, CellStatesIt end);
}

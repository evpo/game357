#pragma once
#include "game_state.h"

namespace Game357
{
    // Initiates the move by human player
    // returns: true if Human has won
    bool MoveHuman(std::vector<CellStates> &game_state, CellStatesIt begin, CellStatesIt end);

    // Initiates the move by the computer
    // returns: true if Computer has won
    bool MoveComputer(std::vector<CellStates> &game_state, CellStatesIt begin, CellStatesIt end);
}

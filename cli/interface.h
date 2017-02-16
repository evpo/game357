#pragma once
#include <tuple>
#include "game_state.h"
namespace Game357
{
    void PrintGameState(const std::vector<CellStates> &game_state);
    // Prompt returns validated move. It returns end iterators if the game is cancelled by the player
    std::tuple<CellStatesIt, CellStatesIt> PromptHuman(std::vector<CellStates> &game_state);

}

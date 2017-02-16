#include "game_loop.h"
#include "assert.h"
#include <algorithm>
#include "game_intellect.h"

using namespace std;
using namespace Game357;

namespace
{
    bool CheckIfWon(std::vector<CellStates> &game_state)
    {
        if(std::count(game_state.begin(), game_state.end(), CellStates::Set) == 14)
            return true;
        return false;
    }
}
namespace Game357
{
    // Initiates the move by human player
    // returns: true if Human has won
    bool MoveHuman(std::vector<CellStates> &game_state, CellStatesIt begin, CellStatesIt end)
    {
        MakeMove(begin, end);
        if(CheckIfWon(game_state))
            return true;
        return false;
    }

    // Initiates the move by the computer
    // returns: true if Computer has won
    bool MoveComputer(GameState &game_state, CellStatesIt begin, CellStatesIt end)
    {
        MakeMove(begin, end);
        if(CheckIfWon(game_state))
            return true;
        return false;
    }
}

#include "game_intellect.h"
#include "adapter_2003.h"
#include "legacy_ai_2001.h"

namespace Game357
{
    std::tuple<CellStatesIt, CellStatesIt> FindBestMove(GameState &game_state)
    {
        using namespace Game357::Legacy;
        State2003 buffer = ConvertTo2003(game_state);
        CalculateComputerMove(buffer.data());
        return FindNewMove(game_state, buffer);
    }
}

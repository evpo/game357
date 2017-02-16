#include "adapter_2003.h"
#include "assert.h"

namespace Game357
{
    using State2003 = std::vector<char>;
    State2003 ConvertTo2003(GameState &game_state)
    {
        State2003 buffer;
        for(auto cell_state : game_state)
        {
            buffer.push_back(cell_state == CellStates::Set ? '1' : '0');
        }
        buffer.insert(buffer.begin() + 3, '!');
        buffer.insert(buffer.begin() + 9, '!');
        buffer.push_back('\0');
        assert(buffer.size() == 18);
        return buffer;
    }

    std::tuple<CellStatesIt, CellStatesIt> FindNewMove(GameState &game_state,
            const State2003 &after)
    {
        State2003 buffer = after;
        buffer.erase(buffer.begin() + 9);
        buffer.erase(buffer.begin() + 3);
        buffer.resize(15);
        bool begin_found = false;
        bool end_found = false;
        CellStatesIt begin = game_state.begin();
        CellStatesIt end = game_state.end();
        for(auto c : buffer)
        {
            if(!begin_found && c == '1' && *begin == CellStates::Open)
            {
                begin_found = true;
                end = begin;
            }

            if(!begin_found)
                begin++;

            if(begin_found && c == '1' && *end == CellStates::Open)
            {
                end_found = true;
                end++;
            }
            else if(end_found)
            {
                break;
            }
        }
        return make_tuple(begin, end);
    }
}

#include "interface.h"
#include <vector>
#include <iostream>
#include "input_parser.h"
#include "validation.h"

using namespace std;

namespace Game357
{
    void PrintGameState(const std::vector<CellStates> &game_state)
    {
        vector<string> markers = {
            "| 1| 2| 3|",
            "| 4| 5| 6| 7| 8|",
            "| 9|10|11|12|13|14|15|",
        };

        int index = 0;
        int marker_index = 0;
        for(auto it = game_state.begin(); it != game_state.end(); it++, index++)
        {
            if(index == 0 || index == 3 || index == 8)
            {
                if(index != 0)
                    cout << endl;
                cout << markers[marker_index++] << endl;
                cout << "|";
            }

            cout << " " << (*it == CellStates::Set ? "X" : " ") << "|";
        }
        cout << endl;
    }

    // Prompt returns validated move. It returns end iterators if the game is cancelled by the player
    std::tuple<CellStatesIt, CellStatesIt> PromptHuman(std::vector<CellStates> &game_state)
    {
        bool valid_input = false;
        CellStatesIt begin = game_state.end();
        CellStatesIt end = game_state.end();
        while(!valid_input)
        {
            cout << "Enter range (From-To and 0 to exit game)? ";
            string range;
            cin >> range;
            auto range_strings = ParseRange(range);
            if(get<0>(range_strings) == "" || get<0>(range_strings) == "0")
                return make_tuple(game_state.end(), game_state.end());

            begin = game_state.begin() + stoi(get<0>(range_strings)) - 1;
            end = game_state.begin() + stoi(get<1>(range_strings));
            valid_input = IsMoveValid(game_state, begin, end);
            if(!valid_input)
                cout << "Invalid input. Try again" << endl;
        }
        return std::make_tuple(begin, end);
    }
}

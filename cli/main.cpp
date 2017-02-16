#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include "version.h"
#include "cli_parser.hpp"
#include "game_loop.h"
#include "game_state.h"
#include "interface.h"
#include "validation.h"
#include "game_intellect.h"
#include "assert.h"

using namespace std;
using namespace stlplus;
using namespace Game357;

namespace Game357
{
    void PrintUsage()
    {
        const char *usage =
            VER_PRODUCTNAME_STR " " VER_PRODUCTVERSION_STR "\n"
            "\n"
            "Usage: game357 -help|[options]\n"
            "Game 357\n"
            "-h|-help this text\n"
            "-c|-comp-first computer moves first\n"
            "-n|-name <your-name> (default: Player1)\n";

        std::cout << usage << std::endl;
    }
}

int main(int, char *argv[])
{
    cli_definitions_t cli_defs = {
        {
            "help",
            cli_kind_t::cli_switch_kind,
            cli_mode_t::cli_single_mode,
            "",
            ""
        },
        {
            "comp-first",
            cli_kind_t::cli_value_kind,
            cli_mode_t::cli_single_mode,
            "",
            ""
        },
        {
            "name",
            cli_kind_t::cli_value_kind,
            cli_mode_t::cli_single_mode,
            "",
            ""
        },
        {
            "",
            cli_kind_t::cli_value_kind,
            cli_mode_t::cli_single_mode,
            "",
            ""
        },
        END_CLI_DEFINITIONS,
    };

    message_handler messages(std::cerr);
    cli_parser parser(&cli_defs[0], messages);
    if(!parser.parse(argv))
    {
        PrintUsage();
        exit(1);
    }

    string name = "Player1";
    bool computer_first = false;
    for(unsigned i = 0; i < parser.size(); i++)
    {
        if(parser.name(i) == "help")
        {
            PrintUsage();
            exit(0);
        }
        else if(parser.name(i) == "name")
        {
            name = parser.string_value(i);
        }
        else if(parser.name(i) == "comp-first")
        {
            computer_first = true;
        }
        else
        {
            PrintUsage();
            exit(1);
        }
    }

    std::vector<CellStates> game_state = GetGameState();

    PrintGameState(game_state);
    bool human_won = false;
    bool computer_won = false;
    while(!human_won && !computer_won)
    {
        if(!computer_first)
        {
            std::tuple<CellStatesIt, CellStatesIt> move = PromptHuman(game_state);
            auto begin = std::get<0>(move);
            auto end = std::get<1>(move);
            if(begin == game_state.end())
            {
                // game is cancelled
                cout << "Empty range. Game is cancelled" << endl;
                break;
            }
            human_won = MoveHuman(game_state, begin, end);
            cout << endl;
            PrintGameState(game_state);
        }
        else
        {
            computer_first = false;
        }

        if(human_won)
            continue;

        cout << endl;
        cout << "Computer moves..." << endl;
        auto tpl = FindBestMove(game_state);
        assert(IsMoveValid(game_state, get<0>(tpl), get<1>(tpl)));
        computer_won = MoveComputer(game_state, get<0>(tpl), get<1>(tpl));
        PrintGameState(game_state);
    }

    cout << endl;

    if(human_won)
    {
        cout << "You won! :)" << endl;
    }
    else if(computer_won)
    {
        cout << "Computer won again! :(" << endl;
    }
    else
    {
        cout << "Game cancelled" << endl;
    }

    return 0;
}

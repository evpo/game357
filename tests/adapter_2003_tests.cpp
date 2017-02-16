#include <string>
#include "gtest/gtest.h"
#include "adapter_2003.h"

using namespace std;

namespace Game357
{
    namespace UnitTests
    {
        TEST(Adapter2003, When_ConvertTo2003_receives_state_It_outputs_good_chars)
        {
            //Arrange
            GameState game_state(15, CellStates::Open);
            std::fill_n(game_state.begin() + 3, 5, CellStates::Set);

            //Act
            State2003 state_2003 = ConvertTo2003(game_state);

            //Assert
            string state_2003_str(state_2003.data(), state_2003.size() - 1);
            ASSERT_EQ("000!11111!0000000", state_2003_str);
        }

        TEST(Adapter2003, When_ConvertTo2003_receives_edge_case_It_outputs_good_chars)
        {
            //Arrange
            GameState game_state(15, CellStates::Open);
            game_state[0] = CellStates::Set;
            game_state[2] = CellStates::Set;
            game_state[8] = CellStates::Set;
            game_state[14] = CellStates::Set;

            //Act
            State2003 state_2003 = ConvertTo2003(game_state);

            //Assert
            string state_2003_str(state_2003.data(), state_2003.size() - 1);
            ASSERT_EQ("101!00000!1000001", state_2003_str);
        }

        TEST(Adapter2003, When_FindNewMove_given_cells_in_middle_It_outputs_tuple)
        {
            //Arrange
            GameState game_state(15, CellStates::Open);
            std::fill_n(game_state.begin() + 3, 5, CellStates::Set);
            string after_str = "000!11111!1110000";
            State2003 after(after_str.data(), after_str.data() + after_str.size());

            //Act
            auto tpl = FindNewMove(game_state, after);

            //Assert
            ASSERT_EQ(8, get<0>(tpl) - game_state.begin());
            ASSERT_EQ(11, get<1>(tpl) - game_state.begin());
        }

        TEST(Adapter2003, When_FindNewMove_finds_set_cells_between_set_cells_It_outputs_tuple)
        {
            //Arrange
            GameState game_state(15, CellStates::Open);
            std::fill_n(game_state.begin(), 3, CellStates::Set);
            std::fill(game_state.begin() + 8, game_state.end(), CellStates::Set);
            string after_str = "111!11110!1111111";
            State2003 after(after_str.data(), after_str.data() + after_str.size());

            //Act
            auto tpl = FindNewMove(game_state, after);

            //Assert
            ASSERT_EQ(3, get<0>(tpl) - game_state.begin());
            ASSERT_EQ(7, get<1>(tpl) - game_state.begin());
        }

        TEST(Adapter2003, When_FindNewMove_given_last_cell_It_outputs_tuple)
        {
            //Arrange
            GameState game_state(15, CellStates::Open);
            string after_str = "000!00000!0000001";
            State2003 after(after_str.data(), after_str.data() + after_str.size());

            //Act
            auto tpl = FindNewMove(game_state, after);

            //Assert
            ASSERT_EQ(14, get<0>(tpl) - game_state.begin());
            ASSERT_EQ(15, get<1>(tpl) - game_state.begin());
        }

        TEST(Adapter2003, When_FindNewMove_given_first_row_It_outputs_tuple)
        {
            //Arrange
            GameState game_state(15, CellStates::Open);
            string after_str = "111!00000!0000000";
            State2003 after(after_str.data(), after_str.data() + after_str.size());

            //Act
            auto tpl = FindNewMove(game_state, after);

            //Assert
            ASSERT_EQ(0, get<0>(tpl) - game_state.begin());
            ASSERT_EQ(3, get<1>(tpl) - game_state.begin());
        }
    }
}

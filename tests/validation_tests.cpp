#include <string>
#include "gtest/gtest.h"
#include "validation.h"

using namespace std;

namespace Game357
{
    namespace UnitTests
    {
        class ValidationFixture : public ::testing::Test
        {
            protected:
                GameState state_;

                virtual void SetUp()
                {
                    state_.resize(15, CellStates::Open);
                }

                virtual void TearDown()
                {
                    state_.clear();
                }
        };

        TEST_F(ValidationFixture, When_move_in_rows_Returns_false)
        {
            //Arrange

            //Act
            bool result = IsMoveValid(state_, state_.begin(), state_.begin() + 4);

            //Assert
            ASSERT_FALSE(result);
        }

        TEST_F(ValidationFixture, When_set_in_move_Returns_false)
        {
            //Arrange
            state_[2] = CellStates::Set;

            //Act
            bool result = IsMoveValid(state_, state_.begin(), state_.begin() + 3);

            //Assert
            ASSERT_FALSE(result);
        }

        TEST_F(ValidationFixture, When_move_is_in_row_Returns_true)
        {
            //Arrange

            //Act
            bool result = IsMoveValid(state_, state_.begin() + 8, state_.begin() + 15);

            //Assert
            ASSERT_TRUE(result);
        }
    }
}

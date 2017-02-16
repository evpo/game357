#include <string>
#include "gtest/gtest.h"
#include "input_parser.h"

using namespace std;

namespace Game357
{
    namespace UnitTests
    {
        TEST(InputParserTests, When_range_is_passed_Two_numbers_returned)
        {
            //Arrange
            string name = "1-3";

            //Act
            auto tpl = ParseRange(name);

            //Assert
            ASSERT_EQ("1", std::get<0>(tpl));
            ASSERT_EQ("3", std::get<1>(tpl));
        }

        TEST(InputParserTests, When_one_number_given_Two_numbers_returned)
        {
            //Arrange
            string name = "3";

            //Act
            auto tpl = ParseRange(name);

            //Assert
            ASSERT_EQ("3", std::get<0>(tpl));
            ASSERT_EQ("3", std::get<1>(tpl));
        }
    }
}

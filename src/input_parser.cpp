#include "input_parser.h"
#include "regex"

using namespace std;

namespace Game357
{
    std::tuple<std::string, std::string> ParseRange(const std::string &input)
    {
        auto invalid_result = make_tuple<string, string>("", "");
        regex rgx("([0-9]{1,2})-([0-9]{1,2})");
        smatch match;
        if(!regex_search(input, match, rgx))
        {
            if(regex_match(input, regex("[0-9]{1,2}")))
                return make_tuple(input, input);

            return invalid_result;
        }

        if(match.size() < 3)
            return invalid_result;

        return make_tuple<string, string>(match[1], match[2]);
    }
}

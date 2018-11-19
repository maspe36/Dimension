//
// Created by Sam on 11/18/2018.
//

#include <catch.hpp>

#include "../../src/Network/Connection.hpp"

TEST_CASE("Sanitized Buffer Reading")
{
    auto inputs = {"test\r", "test\r\n", "test\n"};
    std::string output = "test";

    for (auto input : inputs)
    {
        REQUIRE(Dimension::Network::sanitize(input) == output);
    }
}

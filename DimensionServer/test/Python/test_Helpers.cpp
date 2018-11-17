//
// Created by Sam on 11/15/2018.
//

#include <catch.hpp>
#include "../../src/Python/Helpers.hpp"
#include "../../src/Game/Card.hpp"

#include <pybind11/embed.h>
namespace py = pybind11;

TEST_CASE("Normal Helper Usage")
{
    py::scoped_interpreter guard{};

    try
    {
        SECTION("Configure Path For .so Python Modules")
        {
            Dimension::Python::configurePythonPath();

            REQUIRE(py::module::import("sys").attr("path").contains("../src/Python"));

            auto name = "Foo";

            auto script = R"(
from Game import Card

class Foo(Card):
    def __init__(self, name="Foo"):
        super().__init__(name)
            )";

            SECTION("Create Example Card")
            {
                auto card = Dimension::Python::createCard(name, script);

                REQUIRE(card != nullptr);
                REQUIRE(card->name == name);
            }

            SECTION("Multiple Card Benchmark")
            {
                int n = 1000;

                for (int i = 0; i < n; i++)
                {
                    Dimension::Python::createCard(name, script);
                }
            }
        }
    }
    catch (const py::error_already_set &e)
    {
        FAIL_CHECK(e.what());
    }
    catch (const std::runtime_error &e)
    {
        FAIL_CHECK(e.what());
    }
}

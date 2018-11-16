//
// Created by Sam on 11/11/2018.
//

#include <catch.hpp>

#include <pybind11/embed.h>
namespace py = pybind11;

TEST_CASE("Embedded interpreter")
{
    py::scoped_interpreter guard{};
    py::print("Hello, World!");
}

TEST_CASE("Embedded Module")
{
    py::scoped_interpreter guard{};

    try
    {
        py::module::import("sys").attr("path").cast<py::list>().append("../src/Python");

        auto game = py::module::import("Game");
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
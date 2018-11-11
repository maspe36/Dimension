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
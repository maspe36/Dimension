//
// Created by Sam on 11/11/2018.
//

#include <catch.hpp>
#include <string>

#include <pybind11/embed.h>
namespace py = pybind11;

TEST_CASE("Embedded interpreter")
{
    py::scoped_interpreter guard{};
    try
    {
        SECTION("Correct Python Version")
        {
            auto correctVersion = "3.6.6";
            auto sys = py::module::import("sys");

            auto version_info = sys.attr("version_info");

            int major = version_info.attr("major").cast<int>();
            int minor = version_info.attr("minor").cast<int>();
            int micro = version_info.attr("micro").cast<int>();

            auto version = std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(micro);

            CHECK(version == correctVersion);
        }

        SECTION("Import module")
        {
            py::module::import("sys").attr("path").cast<py::list>().append("../src/Python");
            auto game = py::module::import("Game");
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

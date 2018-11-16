//
// Created by Sam on 11/15/2018.
//

#include "Helpers.hpp"
#include "../Game/Card.hpp"

#include <pybind11/embed.h>

namespace py = pybind11;

Dimension::Game::Card::pointer Dimension::Python::createCard(const std::string& name, const std::string& script)
{
    py::exec(script);
    py::module scope = py::module::import("__main__");
    auto pyCard = scope.attr(name.c_str())();
    return pyCard.cast<std::shared_ptr<Game::Card>>();
}

void Dimension::Python::configurePythonPath()
{
    py::module::import("sys").attr("path").cast<py::list>().append("../src/Python");
}

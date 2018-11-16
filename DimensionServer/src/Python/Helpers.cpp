//
// Created by Sam on 11/15/2018.
//

#include "Helpers.hpp"
#include "../Game/Card.hpp"

#include <pybind11/embed.h>

namespace py = pybind11;

pybind11::object getPythonInstance(const std::string &name)
{
    return pybind11::module::import("__main__").attr(name.c_str())();
}

Dimension::Game::Card::pointer Dimension::Python::createCard(const std::string& name, const std::string& script)
{
    py::exec(script);
    auto pyCard = getPythonInstance(name);
    return pyCard.cast<Dimension::Game::Card::pointer>();
}

void Dimension::Python::configurePythonPath()
{
    py::module::import("sys").attr("path").cast<py::list>().append("../src/Python");
}

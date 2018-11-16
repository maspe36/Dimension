//
// Created by Sam on 11/11/2018.
//

#ifndef DIMENSIONSERVER_MODULE_HPP
#define DIMENSIONSERVER_MODULE_HPP


#include "../Game/Card.hpp"
#include <pybind11/embed.h>

namespace py = pybind11;

PYBIND11_MODULE(Game, m)
{
    py::class_<Dimension::Game::Card, std::shared_ptr<Dimension::Game::Card>> (m, "Card")
            .def(py::init<const std::string&>(),
                 py::arg("name"))
            .def_readwrite("name", &Dimension::Game::Card::name);
}


#endif //DIMENSIONSERVER_MODULE_HPP

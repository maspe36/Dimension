//
// Created by Sam on 11/15/2018.
//

#ifndef DIMENSIONSERVER_FACTORY_HPP
#define DIMENSIONSERVER_FACTORY_HPP


#include <memory>

namespace Dimension
{
    namespace Game
    {
        class Card;
    }

    namespace Python
    {
        std::shared_ptr<Game::Card> createCard(const std::string& name, const std::string& script);
        void configurePythonPath();
    }
}


#endif //DIMENSIONSERVER_FACTORY_HPP

//
// Created by Sam on 11/10/2018.
//

#ifndef DIMENSIONSERVER_CARD_HPP
#define DIMENSIONSERVER_CARD_HPP


#include <memory>

namespace Dimension
{
    namespace Game
    {
        class Card : public std::enable_shared_from_this<Card>
        {
        public:
            using pointer = std::shared_ptr<Card>;

            std::string name;

            explicit Card(const std::string& name);
        };
    }
}


#endif //DIMENSIONSERVER_CARD_HPP

//
// Created by Sam on 10/28/2018.
//

#ifndef DIMENSIONSERVER_LOBBY_HPP
#define DIMENSIONSERVER_LOBBY_HPP


#include "Connection.hpp"
#include <set>

namespace Dimension
{
    namespace Network
    {
        class Server;

        template <typename T>
        class Lobby
        {
        public:
            using pointer = std::shared_ptr<T>;
            using handlerFunction = std::function<void(Server*, pointer)>;

            Lobby(Server* server, handlerFunction handler);

            void join(pointer connection);
            void leave(pointer connection);
            void disconnect(pointer connection);
            bool contains(pointer connection);

            size_t size();

        private:
            std::vector<pointer> connections;
            Server* server;
            handlerFunction handler;
        };
    }
}


#endif //DIMENSIONSERVER_LOBBY_HPP

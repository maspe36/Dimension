//
// Created by Sam on 10/28/2018.
//

#ifndef DIMENSIONSERVER_LOBBY_HPP
#define DIMENSIONSERVER_LOBBY_HPP


#include "Connection.hpp"
#include <set>

namespace Network
{
    class Server;

    using handlerFunction = std::function<void(Server*, Connection::pointer)>;

    class Lobby
    {
    public:
        Lobby(Server* server, handlerFunction handler);

        void join(Connection::pointer connection);
        void leave(Connection::pointer connection);
        void disconnect(Connection::pointer connection);
        bool contains(Connection::pointer connection);

        size_t size();

    private:
        std::set<Connection::pointer> connections;
        Server* server;
        handlerFunction handler;
    };
}


#endif //DIMENSIONSERVER_LOBBY_HPP

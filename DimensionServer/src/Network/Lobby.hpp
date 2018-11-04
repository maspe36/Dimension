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

    class Lobby
    {
    public:
        explicit Lobby(Server* server);

        void join(Connection::pointer connection);
        void leave(Connection::pointer connection);
        void disconnect(Connection::pointer connection);

        size_t size();

    private:
        std::set<Connection::pointer> connections;
        Server* server;

        void handler(Connection::pointer connection);
    };
}


#endif //DIMENSIONSERVER_LOBBY_HPP

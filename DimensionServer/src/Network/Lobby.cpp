#include <utility>

//
// Created by Sam on 10/28/2018.
//

#include "Lobby.hpp"

#include <boost/log/trivial.hpp>

Dimension::Network::Lobby::Lobby(Network::Server* server, Network::handlerFunction handler): server(server),
                                                                                             handler(std::move(handler))
{}

void Dimension::Network::Lobby::join(Connection::pointer connection)
{
    connections.insert(connection);
    connection->listen(
            [=] (Network::Connection::pointer connection, const boost::system::error_code& err)
            {
                if (err)
                {
                    connection->logDisconnect(err);
                    disconnect(connection);
                }
                else
                {
                    handler(server, connection);
                }
            });
}

void Dimension::Network::Lobby::leave(Connection::pointer connection)
{
    connections.erase(connection);
}

void Dimension::Network::Lobby::disconnect(Network::Connection::pointer connection)
{
    connections.erase(connection);
    connection->close();
}

bool Dimension::Network::Lobby::contains(Network::Connection::pointer connection)
{
    return connections.find(connection) != connections.end();
}

size_t Dimension::Network::Lobby::size()
{
    return connections.size();
}

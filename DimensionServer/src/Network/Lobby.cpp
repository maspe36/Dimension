#include <utility>

//
// Created by Sam on 10/28/2018.
//

#include "Lobby.hpp"

#include <boost/log/trivial.hpp>

template <typename T>
Dimension::Network::Lobby<T>::Lobby(Server* server, handlerFunction handler): server(server),
                                                                              handler(std::move(handler))
{}

template <typename T>
void Dimension::Network::Lobby<T>::join(pointer connection)
{
    connections.push_back(connection);
    connection->template listen<pointer>(
            [=] (pointer connection, const boost::system::error_code& err)
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

template <typename T>
void Dimension::Network::Lobby<T>::leave(pointer connection)
{
    connections.erase(std::remove(begin(connections), end(connections), connection), end(connections));
}

template <typename T>
void Dimension::Network::Lobby<T>::disconnect(pointer connection)
{
    connections.erase(std::remove(begin(connections), end(connections), connection), end(connections));
    connection->close();
}

template <typename T>
bool Dimension::Network::Lobby<T>::contains(pointer connection)
{
    return std::find(connections.begin(), connections.end(), connection) != connections.end();
}

template <typename T>
size_t Dimension::Network::Lobby<T>::size()
{
    return connections.size();
}

template class Dimension::Network::Lobby<Dimension::Network::Connection>;
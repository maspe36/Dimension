//
// Created by Sam on 10/28/2018.
//

#include "Lobby.hpp"

#include <boost/log/trivial.hpp>

Network::Lobby::Lobby(Server* server) : server(server)
{}

void Network::Lobby::join(Connection::pointer connection)
{
    connections.insert(connection);
    connection->listen(
            [=] (Network::Connection::pointer connection, const boost::system::error_code& err)
            {
                if (err)
                {
                    BOOST_LOG_TRIVIAL(error) << connection->getAddress() << " disconnected (" << err.message() << ")";
                    disconnect(connection);
                }
                else
                {
                    handler(connection);
                }
            });
}

void Network::Lobby::leave(Connection::pointer connection)
{
    connections.erase(connection);
    connection->cancel();
}

void Network::Lobby::disconnect(Network::Connection::pointer connection)
{
    connections.erase(connection);
    connection->close();
}

size_t Network::Lobby::size()
{
    return connections.size();
}

void Network::Lobby::handler(Network::Connection::pointer connection)
{
    std::string data = connection->readBuffer();
    BOOST_LOG_TRIVIAL(info) << "Message from " << connection->getAddress() << ": " << data;
    connection->write(data);
}

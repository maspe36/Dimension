//
// Created by Sam on 11/7/2018.
//

#include "Handlers.hpp"
#include "Server.hpp"
#include <boost/log/trivial.hpp>

const void Dimension::Network::menuHandler(Network::Server* server, Network::Connection::pointer connection)
{
    connection->write("menuHandler");

    std::string data = connection->readBuffer();

    if (data == "queue")
    {
        server->beginQueue(connection);
        connection->write("queueing...");
    }

    if (data == "test")
    {
        server->cancelQueue(connection);
        connection->write("queue successfully left");
    }
}

const void Dimension::Network::queueHandler(Network::Server* server, std::shared_ptr<Network::Connection> connection)
{
    connection->write("queueHandler");

    std::string data = connection->readBuffer();
    connection->write(data);

    if (data == "cancel")
    {
        server->cancelQueue(connection);
        connection->write("returned to lobby");
    }
}

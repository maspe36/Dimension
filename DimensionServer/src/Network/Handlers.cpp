//
// Created by Sam on 11/7/2018.
//

#include "Handlers.hpp"
#include "Server.hpp"
#include <boost/log/trivial.hpp>

const void Network::menuHandler(Network::Server* server, Network::Connection::pointer connection)
{
    connection->write("menuHandler");

    std::string data = connection->readBuffer();

    if (data == "queue")
    {
        // Move this connection to the queue lobby
        server->beginQueue(connection);
        connection->write("queueing...");
    }
}

const void Network::queueHandler(Network::Server* server, std::shared_ptr<Network::Connection> connection)
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

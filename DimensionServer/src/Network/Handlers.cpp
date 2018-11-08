//
// Created by Sam on 11/7/2018.
//

#include "Handlers.hpp"
#include "Server.hpp"
#include <boost/log/trivial.hpp>

const void Network::menuHandler(Network::Server* server, Network::Connection::pointer connection)
{
    std::string data = connection->readBuffer();

    if (data == "queue")
    {
        // Move this connection to the queue lobby
        server->moveConnection(connection, &server->lobby, &server->queue);

        if (server->queue.contains(connection))
        {
            connection->write("queueing...");
        }
        else
        {
            connection->write("queueing failed");
        }
    }
}

const void Network::queueHandler(Network::Server* server, std::shared_ptr<Network::Connection> connection)
{
    std::string data = connection->readBuffer();
    connection->write(data);

    if (data == "cancel")
    {
        server->moveConnection(connection, &server->queue, &server->lobby);

        if (server->lobby.contains(connection))
        {
            connection->write("returned to lobby");
        }
        else
        {
            connection->write("canceling queue failed");
        }
    }
}

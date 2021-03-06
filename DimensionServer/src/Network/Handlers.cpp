//
// Created by Sam on 11/7/2018.
//

#include "Handlers.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include <boost/log/trivial.hpp>

const void Dimension::Network::connectionToClientHandler(Server* server, Connection::pointer connection)
{
    connection->write("connectionToClientHandler");

    std::string data = connection->readBuffer();

    if (data == "join")
    {
        server->joinLobby(connection);
        connection->write("joining lobby...");
    }
}

const void Dimension::Network::menuHandler(Server* server, Client::pointer client)
{
    client->connection->write("menuHandler");

    std::string data = client->connection->readBuffer();

    if (data == "queue")
    {
        server->beginQueue(client);
        client->connection->write("queueing...");
    }
}

const void Dimension::Network::queueHandler(Server* server, Client::pointer client)
{
    client->connection->write("queueHandler");

    std::string data = client->connection->readBuffer();
    client->connection->write(data);

    if (data == "cancel")
    {
        server->cancelQueue(client);
        client->connection->write("returned to lobby");
    }
}

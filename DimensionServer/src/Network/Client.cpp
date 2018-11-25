#include <utility>

//
// Created by Sam on 11/25/2018.
//

#include "Client.hpp"
#include "Connection.hpp"

Dimension::Network::Client::Client(std::shared_ptr<Connection> connection) : connection(std::move(connection))
{}

void Dimension::Network::Client::listen(const Client::pointer &self, const std::function<void(std::shared_ptr<Client>, const boost::system::error_code &)> &handler)
{
    connection->listen(self, handler);
}

void Dimension::Network::Client::write(const std::string &data)
{
    connection->write(data);
}

void Dimension::Network::Client::close()
{
    connection->close();
}

void Dimension::Network::Client::logDisconnect(const boost::system::error_code &err)
{
    connection->logDisconnect(err);
}


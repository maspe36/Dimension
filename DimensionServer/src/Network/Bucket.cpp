//
// Created by Sam on 10/28/2018.
//

#include "Bucket.hpp"

#include <boost/log/trivial.hpp>

Network::Bucket::Bucket()
= default;

void Network::Bucket::start(Connection::pointer connection)
{
    connections.insert(connection);
    connection->listen(
            [=] (Network::Connection::pointer connection, const boost::system::error_code& err)
            {
                if (err)
                {
                    BOOST_LOG_TRIVIAL(error) << connection->getAddress() << " disconnected (" << err.message() << ")";
                    stop(connection);
                }
                else {
                    this->handler(connection);
                }
            });
}

void Network::Bucket::stop(Connection::pointer connection)
{
    connections.erase(connection);
    connection->close();
}

size_t Network::Bucket::size()
{
    return connections.size();
}

void Network::Bucket::handler(Network::Connection::pointer connection)
{
    std::string data = connection->readBuffer();
    BOOST_LOG_TRIVIAL(info) << "Message from " << connection->getAddress() << ": " << data;
    connection->write(data);
}

//
// Created by Sam on 10/26/2018.
//

#include "Server.hpp"
#include "Handlers.hpp"

#include <ifaddrs.h>
#include <boost/log/trivial.hpp>


Dimension::Network::Server::Server(boost::asio::io_service &ios, unsigned short port) : ios(ios),
                                                                                        port(port),
                                                                                        ipAddress(getAddress()),
                                                                                        acceptor(ios, tcp::endpoint(tcp::v4(), port)),
                                                                                        lobby(this, Network::menuHandler),
                                                                                        queue(this, Network::queueHandler)
{
    listen();
    logStatus();
}

void Dimension::Network::Server::listen()
{
    std::shared_ptr<Connection> connection = std::make_shared<Connection>(ios);
    acceptor.async_accept(
        connection->getSocket(),
        [connection, this] (const boost::system::error_code &err)
        {
            if (!err)
            {
                connection->logConnect();
                lobby.join(connection);

                listen();
            }
            else
            {
                BOOST_LOG_TRIVIAL(error) << err.message();
                connection->shared_from_this().reset();
            }
        });
}

void Dimension::Network::Server::logStatus()
{
    BOOST_LOG_TRIVIAL(info) << "Server started";
    BOOST_LOG_TRIVIAL(info) << "IP: " << getAddress();
    BOOST_LOG_TRIVIAL(info) << "Port: " << std::to_string(port);
    BOOST_LOG_TRIVIAL(info) << "Listening...";
}

void Dimension::Network::Server::logLobby()
{
    BOOST_LOG_TRIVIAL(info) << "Menu Lobby: " << lobby.size() << " connection(s)";
    BOOST_LOG_TRIVIAL(info) << "Queue Lobby: " << queue.size() << " connection(s)";
}

void Dimension::Network::Server::beginQueue(Connection::pointer connection)
{
    lobby.leave(connection);
    queue.join(connection);
    assert(!lobby.contains(connection));
    assert(queue.contains(connection));
}

void Dimension::Network::Server::cancelQueue(Connection::pointer connection)
{
    queue.leave(connection);
    lobby.join(connection);
    assert(!queue.contains(connection));
    assert(lobby.contains(connection));
}

static const std::string Dimension::Network::getAddress()
{
    std::string defaultIPAddressValue = "Unable to get IP Address";
    std::string ipAddress = defaultIPAddressValue;
    std::string ipFilter = "192";
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char *address;
    char *backupAddress = nullptr;

    getifaddrs (&ifap);
    for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr->sa_family==AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            address = inet_ntoa(sa->sin_addr);

            // If any IP address doesn't start with '192'
            if (strncmp(address, ipFilter.c_str(), ipFilter.size()) != 0) {
                ipAddress = address;
                break;
            } else {
                backupAddress = address;
            }
        }
    }

    freeifaddrs(ifap);

    // If no IP address passed the filter, and we actually found an IP address - assign the last one we touched
    if (ipAddress == defaultIPAddressValue && backupAddress != nullptr) {
        ipAddress = backupAddress;
    }

    return ipAddress;
}

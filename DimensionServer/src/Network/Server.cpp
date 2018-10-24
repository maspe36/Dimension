//
// Created by Sam on 10/20/2018.
//

#include "Server.hpp"
#include <string>
#include <iostream>
#include <ifaddrs.h>
#include <boost/log/trivial.hpp>

using namespace boost::asio;

Network::Server::Server(int port) : ipAddress(getIPAddress()),
                                    port(port),
                                    io_service(),
                                    acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), static_cast<unsigned short>(port)))
{
    logInformation();
}

void Network::Server::logInformation()
{
    BOOST_LOG_TRIVIAL(info) << "IP: " << getIPAddress();
    BOOST_LOG_TRIVIAL(info) << "Port: " << std::to_string(port);
}

void Network::Server::start()
{
    if (isRunning())
    {
        BOOST_LOG_TRIVIAL(warning) << "Server already started";
        return;
    }

    BOOST_LOG_TRIVIAL(info) << "Starting server...";

    io_thread.reset(new boost::thread(
            boost::bind(&boost::asio::io_service::run, &io_service)
    ));

    BOOST_LOG_TRIVIAL(info) << "Listening for connections...";
    handleConnection();

    BOOST_LOG_TRIVIAL(info) << "Server started";
}

void Network::Server::stop()
{
    if (!isRunning())
    {
        BOOST_LOG_TRIVIAL(warning) << "Server already stopped";
        return;
    }

    BOOST_LOG_TRIVIAL(info) << "Stopping server...";

    io_service.stop();
    io_thread->join();

    io_service.reset();
    io_thread.reset();

    BOOST_LOG_TRIVIAL(info) << "Server stopped";
}

void Network::Server::handleConnection()
{
    Client::pointer client = std::make_shared<Client>(acceptor.get_io_service());

    acceptor.async_accept(client->socket, boost::bind(&Network::Server::onConnection, this, client, boost::asio::placeholders::error));
}

void Network::Server::onConnection(Client::pointer client, const boost::system::error_code &error)
{
    if (!error) {
        BOOST_LOG_TRIVIAL(info) << "Client connected from '" << client->getIPAddress() << "'";
    }

    handleConnection();
}

bool Network::Server::isRunning()
{
    return bool(io_thread);
}

std::string Network::Server::getIPAddress() {
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

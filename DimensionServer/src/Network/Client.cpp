//
// Created by Sam on 10/21/2018.
//

#include "Client.hpp"

Network::Client::Client(boost::asio::io_service &io_service) : socket(io_service)
{}

std::string Network::Client::getIPAddress()
{
    return socket.remote_endpoint().address().to_string();
}

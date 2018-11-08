//
// Created by Sam on 10/26/2018.
//

#ifndef DIMENSIONSERVER_SERVER_HPP
#define DIMENSIONSERVER_SERVER_HPP


#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Connection.hpp"
#include "Lobby.hpp"

namespace Network
{
    using boost::asio::ip::tcp;

    class Server
    {
    public:
        Server(boost::asio::io_service& ios, unsigned short port);

        void listen();
        void logStatus();
        void logLobby();

        void moveConnection(Connection::pointer connection, Lobby* source, Lobby* destination);

        Lobby lobby;
        Lobby queue;
    private:

        unsigned short port;
        std::string ipAddress;

        boost::asio::io_service& ios;
        tcp::acceptor acceptor;
    };

    static const std::string getAddress();
}


#endif //DIMENSIONSERVER_SERVER_HPP

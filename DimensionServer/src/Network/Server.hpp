//
// Created by Sam on 10/20/2018.
//

#ifndef DIMENSIONSERVER_SERVER_HPP
#define DIMENSIONSERVER_SERVER_HPP

#include <memory>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include "Client.hpp"

namespace Network
{
    class Server : public std::enable_shared_from_this<Server>
    {
    public:
        explicit Server(int port);

        void logInformation();

        void start();
        void stop();
        void handleConnection();
        void onConnection(Client::pointer client, const boost::system::error_code &error);

        bool isRunning();

        typedef std::shared_ptr<Server> pointer;

    private:
        std::string ipAddress;
        int port;
        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor acceptor;
        boost::scoped_ptr<boost::thread> io_thread;

        std::string getIPAddress();
    };
}

#endif //DIMENSIONSERVER_SERVER_HPP

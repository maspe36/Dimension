//
// Created by Sam on 10/26/2018.
//

#ifndef DIMENSIONSERVER_SESSION_HPP
#define DIMENSIONSERVER_SESSION_HPP


#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace Network
{
    using boost::asio::ip::tcp;

    class Session : public std::enable_shared_from_this<Session>
    {
    public:
        explicit Session(boost::asio::io_service& ios);

        std::string getAddress();
        tcp::socket& getSocket();

        void listen(std::function<void(std::string)> handler);
        void write(std::string data);
        void cancel();
        void close();

    private:
        tcp::socket socket;
        boost::asio::streambuf buffer;

        std::string readBuffer();
    };
}


#endif //DIMENSIONSERVER_SESSION_HPP

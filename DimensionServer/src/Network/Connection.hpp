#include <utility>

//
// Created by Sam on 10/26/2018.
//

#ifndef DIMENSIONSERVER_CONNECTION_HPP
#define DIMENSIONSERVER_CONNECTION_HPP


#include <iostream>
#include <memory>
#include <variant>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "ResponseFunctionHelper.hpp"

namespace Dimension
{
    namespace Network
    {
        using boost::asio::ip::tcp;

        class Connection : public std::enable_shared_from_this<Connection>
        {
        public:
            using pointer = std::shared_ptr<Connection>;

            explicit Connection(boost::asio::io_service& ios);

            static const std::string LINE_FEED;
            static const std::string CARRIAGE_RETURN;
            std::string address;

            std::string getAddress();
            tcp::socket& getSocket();
            std::string readBuffer();

            void listen(const variantPointer& newCaller, const responseFunction& newLobbyLambdaHandler);

            void write(const std::string& data);
            void close();

            void logConnect();
            void logDisconnect(const boost::system::error_code& err);

        private:
            responseFunction lobbyLambdaHandler;
            variantPointer caller;

            tcp::socket socket;
            boost::asio::streambuf buffer;

            void listen();
        };

        std::string sanitize(const std::string &data);
    }
}


#endif //DIMENSIONSERVER_CONNECTION_HPP

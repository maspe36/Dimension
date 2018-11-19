//
// Created by Sam on 10/26/2018.
//

#ifndef DIMENSIONSERVER_CONNECTION_HPP
#define DIMENSIONSERVER_CONNECTION_HPP


#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace Dimension
{
    namespace Network
    {
        using boost::asio::ip::tcp;

        class Connection : public std::enable_shared_from_this<Connection>
        {
        public:
            using pointer = std::shared_ptr<Connection>;
            using responseFunction = std::function<void(pointer, const boost::system::error_code&)>;

            explicit Connection(boost::asio::io_service& ios);

            static const std::string LINE_FEED;
            static const std::string CARRIAGE_RETURN;
            std::string address;

            std::string getAddress();
            tcp::socket& getSocket();
            std::string readBuffer();

            void listen(responseFunction handler);
            void write(const std::string& data);
            void close();

            void logConnect();
            void logDisconnect(const boost::system::error_code& err);

        private:
            responseFunction handler;
            tcp::socket socket;
            boost::asio::streambuf buffer;

            void listen();
        };

        std::string sanitize(const std::string &data);
    }
}


#endif //DIMENSIONSERVER_CONNECTION_HPP

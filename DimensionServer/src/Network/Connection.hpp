//
// Created by Sam on 10/26/2018.
//

#ifndef DIMENSIONSERVER_CONNECTION_HPP
#define DIMENSIONSERVER_CONNECTION_HPP


#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace Network
{
    using boost::asio::ip::tcp;

    class Connection : public std::enable_shared_from_this<Connection>
    {
    public:
        using pointer = std::shared_ptr<Connection>;
        using responseFunction = std::function<void(pointer, const boost::system::error_code&)>;

        explicit Connection(boost::asio::io_service& ios);

        std::string getAddress();
        tcp::socket& getSocket();
        std::string readBuffer();

        void listen(responseFunction handler);
        void write(const std::string& data);
        void cancel();
        void close();

    private:
        static const std::string DELIMITER;

        tcp::socket socket;
        boost::asio::streambuf buffer;
    };
}


#endif //DIMENSIONSERVER_CONNECTION_HPP

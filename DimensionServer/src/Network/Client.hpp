//
// Created by Sam on 10/21/2018.
//

#ifndef DIMENSIONSERVER_CLIENT_HPP
#define DIMENSIONSERVER_CLIENT_HPP

#include <memory>
#include <boost/asio.hpp>

namespace Network
{
    class Client : public std::enable_shared_from_this<Client>
    {
    public:
        boost::asio::ip::tcp::socket socket;

        explicit Client(boost::asio::io_service& io_service);

        std::string getIPAddress();

        typedef std::shared_ptr<Client> pointer;

    private:
        boost::asio::streambuf buffer;

    };
}

#endif //DIMENSIONSERVER_CLIENT_HPP

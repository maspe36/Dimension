//
// Created by Sam on 11/25/2018.
//

#ifndef DIMENSIONSERVER_CLIENT_HPP
#define DIMENSIONSERVER_CLIENT_HPP

#include <memory>
#include <functional>
#include <boost/system/error_code.hpp>
#include <any>
#include "Connection.hpp"


namespace Dimension
{
    namespace Network
    {
        class Client : public std::enable_shared_from_this<Client>
        {
        public:
            using pointer = std::shared_ptr<Client>;
            using responseFunction = std::function<void(pointer, const boost::system::error_code &)>;

            explicit Client(std::shared_ptr<Connection> connection);

            std::shared_ptr<Connection> connection;

            void listen(const Client::pointer &self, const std::function<void(std::shared_ptr<Client>, const boost::system::error_code &)> &handler);
            void close();

            void logDisconnect(const boost::system::error_code &err);
        };
    }
}


#endif //DIMENSIONSERVER_CLIENT_HPP

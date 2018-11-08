//
// Created by Sam on 11/7/2018.
//

#ifndef DIMENSIONSERVER_HANDLERS_HPP
#define DIMENSIONSERVER_HANDLERS_HPP


#include <memory>

namespace Network
{
    class Server;
    class Connection;

    const void menuHandler(Network::Server* server, std::shared_ptr<Connection> connection);
    const void queueHandler(Network::Server* server, std::shared_ptr<Connection> connection);
}


#endif //DIMENSIONSERVER_HANDLERS_HPP

//
// Created by Sam on 11/7/2018.
//

#ifndef DIMENSIONSERVER_HANDLERS_HPP
#define DIMENSIONSERVER_HANDLERS_HPP


#include <memory>

namespace Dimension
{
    namespace Network
    {
        class Server;
        class Client;
        class Connection;

        const void connectionToClientHandler(Server* server, std::shared_ptr<Connection> connection);
        const void menuHandler(Server* server, std::shared_ptr<Client> client);
        const void queueHandler(Server* server, std::shared_ptr<Client> client);
    }
}


#endif //DIMENSIONSERVER_HANDLERS_HPP

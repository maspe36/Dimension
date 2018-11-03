//
// Created by Sam on 10/28/2018.
//

#ifndef DIMENSIONSERVER_SESSIONHANDLER_HPP
#define DIMENSIONSERVER_SESSIONHANDLER_HPP


#include "Connection.hpp"
#include <set>

namespace Network
{
    class SessionHandler
    {
    public:
        SessionHandler();

        void start(Connection::pointer session);
        void stop(Connection::pointer session);

        size_t size();

    private:
        std::set<Connection::pointer> sessions;

        void handler(Connection::pointer session);
    };
}


#endif //DIMENSIONSERVER_SESSIONHANDLER_HPP

//
// Created by Sam on 10/28/2018.
//

#ifndef DIMENSIONSERVER_SESSIONHANDLER_HPP
#define DIMENSIONSERVER_SESSIONHANDLER_HPP


#include "Connection.hpp"
#include <set>

namespace Network
{
    class Bucket
    {
    public:
        Bucket();

        void start(Connection::pointer connection);
        void stop(Connection::pointer connection);

        size_t size();

    private:
        std::set<Connection::pointer> connections;

        void handler(Connection::pointer connection);
    };
}


#endif //DIMENSIONSERVER_SESSIONHANDLER_HPP

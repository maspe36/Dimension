//
// Created by Sam on 10/28/2018.
//

#ifndef DIMENSIONSERVER_SESSIONHANDLER_HPP
#define DIMENSIONSERVER_SESSIONHANDLER_HPP


#include "Session.hpp"
#include <set>

namespace Network
{
    class SessionHandler
    {
    public:
        SessionHandler();

        void start(Session::pointer session);
        void stop(Session::pointer session);

        size_t size();

    private:
        std::set<Session::pointer> sessions;

        void handler(Session::pointer session);
    };
}


#endif //DIMENSIONSERVER_SESSIONHANDLER_HPP

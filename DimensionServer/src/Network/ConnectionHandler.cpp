//
// Created by Sam on 10/28/2018.
//

#include "ConnectionHandler.hpp"

#include <boost/log/trivial.hpp>

Network::SessionHandler::SessionHandler()
= default;

void Network::SessionHandler::start(Connection::pointer session)
{
    sessions.insert(session);
    session->listen(
            [=] (Network::Connection::pointer session, const boost::system::error_code& err)
            {
                if (err)
                {
                    BOOST_LOG_TRIVIAL(error) << session->getAddress() << " disconnected (" << err.message() << ")";
                    stop(session);
                }
                else {
                    this->handler(session);
                }
            });
}

void Network::SessionHandler::stop(Connection::pointer session)
{
    sessions.erase(session);
    session->close();
}

size_t Network::SessionHandler::size()
{
    return sessions.size();
}

void Network::SessionHandler::handler(Network::Connection::pointer session)
{
    std::string data = session->readBuffer();
    BOOST_LOG_TRIVIAL(info) << "Message from " << session->getAddress() << ": " << data;
    session->write(data);
}

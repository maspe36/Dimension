#include <utility>

//
// Created by Sam on 10/26/2018.
//

#include "Connection.hpp"

#include <boost/log/trivial.hpp>


const std::string Dimension::Network::Connection::LINE_FEED = "\n";
const std::string Dimension::Network::Connection::CARRIAGE_RETURN = "\r";

Dimension::Network::Connection::Connection(boost::asio::io_service &ios) : socket(ios)
{
}

std::string Dimension::Network::Connection::getAddress()
{
    if (address.empty())
    {
        address = shared_from_this()->getSocket().remote_endpoint().address().to_string();
    }

    return address;
}

boost::asio::ip::tcp::socket& Dimension::Network::Connection::getSocket()
{
    return socket;
}

std::string Dimension::Network::Connection::readBuffer()
{
    boost::asio::streambuf::const_buffers_type bufs = buffer.data();
    std::string data(
            boost::asio::buffers_begin(bufs),
            boost::asio::buffers_begin(bufs) + buffer.size());

    // Empty the buffer
    buffer.consume(buffer.size());

    // Return everything except the 'LINE_FEED'
    return Dimension::Network::sanitize(data);
}

void Dimension::Network::Connection::write(const std::string& data)
{
    auto finalData = data + LINE_FEED;

    boost::asio::async_write(socket, boost::asio::buffer(finalData.c_str(), finalData.size()),
        [data, this](const boost::system::error_code& err, size_t bytes_transferred)
        {
            if (err)
            {
                BOOST_LOG_TRIVIAL(error) << "Failed to write '" << data << "' to " << getAddress();
            }
        });
}

void Dimension::Network::Connection::close()
{
    socket.close();
}

void Dimension::Network::Connection::logConnect()
{
    BOOST_LOG_TRIVIAL(info) << "Connection from: " << getAddress() << " [" << this << "]";
}

void Dimension::Network::Connection::logDisconnect(const boost::system::error_code& err)
{
    BOOST_LOG_TRIVIAL(error) << getAddress() << " [" << this << "]" << " disconnected (" << err.message() << ")";
}

std::string Dimension::Network::sanitize(std::string const &data)
{
    std::string sanitized = data;
    char ending = sanitized.at(sanitized.size() - 1);

    while (ending == Dimension::Network::Connection::LINE_FEED.at(0) or
           ending == Dimension::Network::Connection::CARRIAGE_RETURN.at(0))
    {
        sanitized = sanitized.substr(0, sanitized.size() - 1);
        ending = sanitized.at(sanitized.size() - 1);
    }

    return sanitized;
}

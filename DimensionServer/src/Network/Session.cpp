//
// Created by Sam on 10/26/2018.
//

#include "Session.hpp"
#include <boost/log/trivial.hpp>

using namespace Network;

const static std::string DELIMITER = "\n";

Network::Session::Session(boost::asio::io_service &ios) : socket(ios)
{
}

std::string Session::getAddress()
{
    return shared_from_this()->getSocket().remote_endpoint().address().to_string();
}

tcp::socket& Network::Session::getSocket()
{
    return socket;
}

void Session::listen(std::function<void(std::string)> handler)
{
    boost::asio::async_read_until(socket, buffer, DELIMITER,
        [handler, this] (const boost::system::error_code &err)
        {
            if (!err)
            {
                handler(readBuffer());
            }
            else
            {
                BOOST_LOG_TRIVIAL(error) << err.message();
            }

            listen(handler);
        });
}

void Session::write(std::string data)
{
    data.append(DELIMITER);

    boost::asio::async_write(socket, boost::asio::buffer(data.c_str(), data.size()),
        [data, this](const boost::system::error_code &err)
        {
            if (err)
            {
                BOOST_LOG_TRIVIAL(error) << "Failed to write '" << data << "' to " << getAddress();
            }
        });
}

void Session::cancel()
{
    socket.cancel();
}

void Session::close()
{
    socket.close();
}

std::string Session::readBuffer()
{
    boost::asio::streambuf::const_buffers_type bufs = buffer.data();
    std::string data(
            boost::asio::buffers_begin(bufs),
            boost::asio::buffers_begin(bufs) + buffer.size());

    // Empty the buffer
    buffer.consume(buffer.size());

    // Return everything except the 'DELIMITER'
    return data.substr(0, data.size() - 1);
}

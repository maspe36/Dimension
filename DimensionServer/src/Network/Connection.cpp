//
// Created by Sam on 10/26/2018.
//

#include "Connection.hpp"

#include <boost/log/trivial.hpp>


using namespace Network;

const static std::string DELIMITER = "\n";

Network::Connection::Connection(boost::asio::io_service &ios) : socket(ios)
{
}

std::string Connection::getAddress()
{
    return shared_from_this()->getSocket().remote_endpoint().address().to_string();
}

tcp::socket& Network::Connection::getSocket()
{
    return socket;
}

std::string Connection::readBuffer()
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

void Connection::listen(std::function<void(Network::Connection::pointer, const boost::system::error_code&)> handler)
{
    auto self(shared_from_this());
    boost::asio::async_read_until(socket, buffer, DELIMITER,
        [handler, this, self] (const boost::system::error_code& err, size_t bytes_transferred)
        {
            handler(self, err);

            if (!err)
            {
                listen(handler);
            }
        });
}

void Connection::write(std::string data)
{
    data.append(DELIMITER);

    boost::asio::async_write(socket, boost::asio::buffer(data.c_str(), data.size()),
        [data, this](const boost::system::error_code& err, size_t bytes_transferred)
        {
            if (err)
            {
                BOOST_LOG_TRIVIAL(error) << "Failed to write '" << data << "' to " << getAddress();
            }
        });
}

void Connection::cancel()
{
    socket.cancel();
}

void Connection::close()
{
    socket.close();
}
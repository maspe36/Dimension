//
// Created by Sam on 10/26/2018.
//

#ifndef DIMENSIONSERVER_CONNECTION_HPP
#define DIMENSIONSERVER_CONNECTION_HPP


#include <iostream>
#include <memory>
#include <any>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

namespace Dimension
{
    namespace Network
    {
        using boost::asio::ip::tcp;

        class Connection : public std::enable_shared_from_this<Connection>
        {
        public:
            using pointer = std::shared_ptr<Connection>;

            explicit Connection(boost::asio::io_service& ios);

            static const std::string LINE_FEED;
            static const std::string CARRIAGE_RETURN;
            std::string address;

            std::string getAddress();
            tcp::socket& getSocket();
            std::string readBuffer();

            template <typename pointer>
            void listen(std::function<void(pointer, const boost::system::error_code&)> newLobbyLambdaHandler)
            {
                lobbyLambdaHandler = newLobbyLambdaHandler;
                listen<pointer>();
            }

            void write(const std::string& data);
            void close();

            void logConnect();
            void logDisconnect(const boost::system::error_code& err);

        private:
            std::any lobbyLambdaHandler;
            tcp::socket socket;
            boost::asio::streambuf buffer;

            template <typename pointer>
            void listen()
            {
                auto self(shared_from_this());
                boost::asio::async_read_until(socket, buffer, LINE_FEED,
                [this, self] (const boost::system::error_code& err, size_t bytes_transferred)
                {
                    using LobbyLambdaType = std::function<void(pointer, const boost::system::error_code&)>;
                    auto castHandler = std::any_cast<LobbyLambdaType>(lobbyLambdaHandler);
                    castHandler(self, err);

                    if (!err)
                    {
                        castHandler = std::any_cast<LobbyLambdaType>(lobbyLambdaHandler);
                        listen<pointer>(castHandler);
                    }
                });
            }
        };

        std::string sanitize(const std::string &data);
    }
}


#endif //DIMENSIONSERVER_CONNECTION_HPP

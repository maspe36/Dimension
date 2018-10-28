#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/log/trivial.hpp>
#include "Network/Server.hpp"

int main(int argc, char *argv[])
{
    try {
        // Create the IO Service
        boost::asio::io_service ios;

        // Create the server which will create session objects
        Network::Server server(ios, 8080);

        // Spin up another thread for the IO Service to listen for incoming connections
        boost::thread io_thread(boost::bind(&boost::asio::io_service::run, &ios));

        // CLI
        BOOST_LOG_TRIVIAL(info) << "Enter the word \"quit\" to exit the program and shut down the server";
        std::string command;
        bool done = false;
        while (!done && std::cin >> command)
        {
            if (command == "quit")
            {
                done = true;
            }

            if (command == "list")
            {
                server.logHandler();
            }
        }

    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

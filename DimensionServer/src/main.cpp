#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include "Network/Server.hpp"

int main(int argc, char *argv[])
{
    try {
        // Create the IO Service
        boost::asio::io_service ios;

        // Create the server which will create session objects
        Network::Server s(ios, 8080);

        // Spin up another thread for the IO Service to listen for incoming connections
        boost::thread io_thread(boost::bind(&boost::asio::io_service::run, &ios));

        // CLI
        while (true) {}
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

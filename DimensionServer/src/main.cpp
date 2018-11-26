#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/log/trivial.hpp>

#include "Python/Helpers.hpp"

#include <pybind11/embed.h>

namespace py = pybind11;

int main(int argc, char *argv[])
{
    try {
        // Create the scoped interpreter
        py::scoped_interpreter guard{};

        // Setup python environment
        Dimension::Python::configurePythonPath();

        // Create the IO Service
        boost::asio::io_service ios;

        // Start UDP server


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
        }

        ios.stop();
        io_thread.join();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

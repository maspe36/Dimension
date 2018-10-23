#include <iostream>
#include <memory>
#include "Network/Server.hpp"

using namespace Network;

int main()
{
    std::shared_ptr<Server> server = std::make_shared<Server>(9001);
    server->start();

    while (server->isRunning()) {}
}

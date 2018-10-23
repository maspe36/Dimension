//
// Created by Sam on 10/21/2018.
//

#include <catch.hpp>
#include "../../src/Network/Server.hpp"

SCENARIO("Server: check if the server is running")
{
    GIVEN("A server")
    {
        std::shared_ptr<Network::Server> server = std::make_shared<Network::Server>(9001);
        THEN("isRunning should be false")
        {
            CHECK(!server->isRunning());
        }
        WHEN("we start the server")
        {
            server->start();
            THEN("isRunning should be true")
            {
                CHECK(server->isRunning());
                WHEN("we stop the server")
                {
                    server->stop();
                    THEN("isRunning should be false")
                    {
                        CHECK(!server->isRunning());
                    }
                }
            }
        }
    }
}

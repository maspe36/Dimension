//
// Created by Sam on 11/25/2018.
//

#ifndef DIMENSIONSERVER_RESPONSEFUNCTIONHELPER_HPP
#define DIMENSIONSERVER_RESPONSEFUNCTIONHELPER_HPP

#include <memory>
#include <variant>
#include <functional>
#include <boost/system/error_code.hpp>

namespace Dimension
{
    namespace Network
    {
        class Client;
        class Connection;

        using variantPointer = std::variant<std::shared_ptr<Client>, std::shared_ptr<Connection>>;

        using clientResponseFunction = std::function<void(const std::shared_ptr<Client>&, const boost::system::error_code &)>;
        using connectionResponseFunction = std::function<void(const std::shared_ptr<Connection>&, const boost::system::error_code &)>;

        using responseFunction = std::variant<clientResponseFunction, connectionResponseFunction>;

        template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
        template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
    }
}

#endif //DIMENSIONSERVER_RESPONSEFUNCTIONHELPER_HPP

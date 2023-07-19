#include <iostream>
#include <asio.hpp>
#include <memory>
#include <functional>
#include "my_session.h"


using namespace std::placeholders;
class Server {
public:
    Server(asio::io_context& io_context, short port)
            : acceptor_(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
              socket_(io_context) {}

    void start() {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept(socket_, std::bind(&Server::handle_accept, this, _1));
    }
    /*
    void handle_accept(const asio::error_code& error) {
        if (!error) {
            std::make_shared<Session>(std::move(socket_))->start();
        }
        do_accept();
    }
    */
    // when a new client connects to server
    // use thread to run the new session and detach it, so that it will not block the main thread
    void handle_accept(const asio::error_code& error) {
        if (!error) {
            std::thread t([this]() {
                std::make_shared<Session>(std::move(socket_))->start();
            });
            t.detach();
        }
        do_accept();
    }
private:
    asio::ip::tcp::acceptor acceptor_;
    asio::ip::tcp::socket socket_;
};

int main() {
    asio::io_service io_service;
    short port = 8000;

    Server server(io_service, port);
    server.start();

    io_service.run();

    return 0;
}

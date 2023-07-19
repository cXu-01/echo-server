#ifndef MY_ECHO_SERVER_MY_SESSION_H
#define MY_ECHO_SERVER_MY_SESSION_H

#include <iostream>
#include <asio.hpp>
#include <memory>
#include <functional>

using namespace std::placeholders;

class Session : public std::enable_shared_from_this<Session> {
public:
    void start();
    Session(asio::ip::tcp::socket socket): socket_(std::move(socket)), buffer_(1024){};

private:
    void do_read();
    void do_write(size_t length);

private:
    asio::ip::tcp::socket socket_;
    std::vector<char> buffer_;
};


#endif //MY_ECHO_SERVER_MY_SESSION_H

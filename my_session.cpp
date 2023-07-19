#include "my_session.h"


void Session::start() {
    std::cout << "New connection from " << socket_.remote_endpoint() << std::endl;
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(asio::buffer(buffer_),
                            [this, self](const asio::error_code& error, size_t bytes_transferred)
                            {
                                if (!error) {
                                    std::cout << "Received message from " << socket_.remote_endpoint() << ": "
                                              << std::string(buffer_.data(), bytes_transferred) << std::endl;
                                    do_write(bytes_transferred);
                                }
                            });
}

void Session::do_write(size_t length) {
    auto self(shared_from_this());
    asio::async_write(socket_, asio::buffer(buffer_.data(), length),
                      [this, self](const asio::error_code& error, size_t bytes_transferred)
                      {
                          if (!error) {
                              do_read();
                          }
                      });
}




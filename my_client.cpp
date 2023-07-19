#include <iostream>
#include <asio.hpp>

using namespace asio::ip;

template<typename Socket>
void communicate(Socket& socket) {
    while (true) {
        std::cout << "Enter message: ";
        std::string message;
        std::getline(std::cin, message);

        asio::write(socket, asio::buffer(message));

        std::array<char, 1024> buffer;
        asio::error_code error;
        size_t length = socket.read_some(asio::buffer(buffer), error);

        if (error == asio::error::eof) {
            std::cout << "Connection closed by peer." << std::endl;
            break;
        } else if (error) {
            throw asio::system_error(error);
        }

        std::cout << "Received message: " << std::string(buffer.data(), length) << std::endl;
    }
}

int main() {
    asio::io_context io_context;
    tcp::socket socket(io_context);
    tcp::resolver resolver(io_context);

    tcp::resolver::results_type endpoints = resolver.resolve("localhost", "8000");

    asio::connect(socket, endpoints);

    communicate(socket);

    return 0;
}

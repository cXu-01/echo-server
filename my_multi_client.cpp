#include <iostream>
#include <asio.hpp>
#include <memory>

using namespace asio::ip;
#include <thread>
#include <random>
#include <chrono>


using namespace asio::ip;

void client_thread(const std::string& message, std::promise<std::string>& result) {
    try {
        asio::io_context io_context;
        tcp::socket socket(io_context);

        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints = resolver.resolve("localhost", "8000");

        // connect to server
        asio::connect(socket, endpoints);

        // send message
        asio::write(socket, asio::buffer(message));

        // get reply
        std::array<char, 1024> buffer;
        asio::error_code error;
        size_t length = socket.read_some(asio::buffer(buffer), error);

        if (error == asio::error::eof) {
            result.set_value("Connection closed by peer.");
        } else if (error) {
            throw asio::system_error(error);
        }

        result.set_value(std::string(buffer.data(), length));
    } catch (std::exception& e) {
        result.set_exception(std::current_exception());
    }
}

int main() {
    asio::io_context io_context;
    tcp::resolver resolver(io_context);

    // get server ip and ports
    tcp::resolver::results_type endpoints = resolver.resolve("localhost", "8000");

    // generate 5 messages randomly，initiate 5 threads and send message
    std::vector<std::string> messages = {"hello1", "world2", "test3", "test4", "test5"};
    std::vector<std::promise<std::string>> promises(5);
    std::vector<std::future<std::string>> futures;
    for (int i = 0; i < 5; ++i) {
        futures.emplace_back(promises[i].get_future());
        std::thread(client_thread, messages[i], std::ref(promises[i])).detach();
    }

    // return result when all threads finished
    for (int i = 0; i < 5; ++i) {
        std::cout << "Received message: " << futures[i].get() << std::endl;
    }

    return 0;
}

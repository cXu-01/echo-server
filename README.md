# echo-server

This repository contains an efficient echo server that listens on port 8000 and returns any incoming messages.

Project Files Description
my_server.cpp
A server implementation using the Asio library. It begins by creating an io_service object, initializing the Server object, and initiating the start() function. It concludes by calling the io_service's run() function to kickstart the event loop and process asynchronous operations. It handles client connections using the Session objects and protects shared resources with a std::lock_guard.

my_session.cpp & my_session.h
These files manage the Session class that tackles the actual communication with the individual client. It is responsible for reading incoming messages and echoing them back to the client.

my_client.cpp
This file houses a template function named "communicate" that works with a Socket type parameter and manages sending and receiving messages on that socket.

my_multi_client.cpp
This file implements a simple multi-threaded TCP client that connects to the server and sends 5 randomly generated messages, each in a separate thread. Synchronization and communication between threads are ensured using std::promise and std::future.

Advanced Concepts Utilized
Asynchronous I/O with Asio library: Offers a high-performance cross-platform library for network and low-level I/O programming.
Templates: Promotes generic coding that is compatible with any type, allowing for code reuse and minimizing redundancy.
Smart pointers: Uses shared_ptr and unique_ptr to manage object lifetimes and prevent memory leaks.
Futures and Promises: Synchronize data between the main thread and client threads.
C++17 and C++20 Features: Like structured bindings, if constexpr, and constexpr if.
Mutex: Protects shared acceptor_ and socket_ member variables from concurrent modification, preventing data races and undefined behavior.

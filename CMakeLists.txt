cmake_minimum_required(VERSION 3.19)
project(My_echo_server)

set(CMAKE_CXX_STANDARD 14)
include_directories(/opt/homebrew/Cellar/asio/1.26.0/include)
add_executable(My_echo_server my_server.cpp my_server.h my_session.cpp my_session.h)
add_executable(My_echo_client my_client.cpp)
add_executable(My_echo_multi_client my_multi_client.cpp)
target_link_libraries(My_echo_server /opt/homebrew/Cellar/asio/1.26.0/include)
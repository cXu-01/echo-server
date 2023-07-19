This project depends on asio, and should run in macOS/Ubuntu System.
install dependencies:
brew install asio
get the version and path of asio /opt/homebrew/Cellar/asio/1.26.0/include
replace the path of asio in CMakeLists.txt include_directories and target_link_libraries
reload the project after making the change.

Run the program:
run my_server.cpp main to establish server
then run my_client.cpp
You can type any message in the terminal and the server will echo it back
run my_multi_client.app

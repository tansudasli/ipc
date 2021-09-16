cmake_minimum_required(VERSION 3.17)
project(socket_programming)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/header)

#run w/
# cmake --build cmake-build-debug --target all -- -j 9
add_executable(tcp_client
        src/tcp/client.c)

add_executable(tcp_server
        src/tcp/server.c)

add_executable(internal_client
        src/internal/client.c)

add_executable(internal_server
        src/internal/server.c)
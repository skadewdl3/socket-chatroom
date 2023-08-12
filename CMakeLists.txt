cmake_minimum_required(VERSION 3.22)
project(SocketChatroom)

set(CMAKE_CXX_STANDARD 17)


add_executable(SocketChatroom main.cpp)


# Adding library for sockets
add_subdirectory("${PROJECT_SOURCE_DIR}/sockets-lib")
target_link_libraries(SocketChatroom PUBLIC SocketsLib)

# Adding library for json
add_subdirectory("${PROJECT_SOURCE_DIR}/json-lib")
target_link_libraries(SocketChatroom PUBLIC JSONLib)

# Adding header file paths for both libraries
target_include_directories(SocketChatroom PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/sockets-lib"
        "${PROJECT_SOURCE_DIR}/json-lib"
)
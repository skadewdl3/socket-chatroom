cmake_minimum_required(VERSION 3.22)
project(SocketChatroom)

set(CMAKE_CXX_STANDARD 17)


add_executable(server server.cpp)
add_executable(client client.cpp)

# Adding library for sockets
add_subdirectory("${PROJECT_SOURCE_DIR}/sockets-lib")
target_link_libraries(server PUBLIC SocketsLib)
target_link_libraries(client PUBLIC SocketsLib)

# Adding library for json
add_subdirectory("${PROJECT_SOURCE_DIR}/json-lib")
target_link_libraries(server PUBLIC JSONLib)
target_link_libraries(client PUBLIC JSONLib)

target_include_directories(server PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/sockets-lib"
        "${PROJECT_SOURCE_DIR}/json-lib"
)
target_include_directories(client PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/sockets-lib"
        "${PROJECT_SOURCE_DIR}/json-lib"
)
cmake_minimum_required(VERSION 3.12)
project(CustomerServiceSystem LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(CustomerServiceSystem
    src/main.cpp
    src/CircularQueue.cpp
)

# Include directories (header files are in src)
target_include_directories(CustomerServiceSystem PRIVATE src)

# Link platform libraries (needed for cpp‑httplib on Windows)
if (WIN32)
    target_link_libraries(CustomerServiceSystem ws2_32)
endif()

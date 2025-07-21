cmake_minimum_required(VERSION 3.10)
project(DocumentationSystemGT)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(doc_sys src/main.cpp src/database.cpp)

find_package(SQLite3 REQUIRED)
target_link_libraries(doc_sys SQLite::SQLite3)

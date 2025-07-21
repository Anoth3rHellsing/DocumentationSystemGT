cmake_minimum_required(VERSION 3.10)
project(DocumentationSystemGT)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(doc_sys src/main.cpp)

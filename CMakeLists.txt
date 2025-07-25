cmake_minimum_required(VERSION 3.10)
project(DocumentationSystemGT VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

enable_testing()

add_executable(doc_sys src/main.cpp src/database.cpp)

find_package(SQLite3 REQUIRED)
target_link_libraries(doc_sys SQLite::SQLite3)

add_executable(test_db tests/test_database.cpp src/database.cpp)
target_link_libraries(test_db SQLite::SQLite3)
add_test(NAME DatabaseTest COMMAND test_db)

cmake_minimum_required(VERSION 3.10)
project(DocumentationSystemGT)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

enable_testing()

add_executable(doc_sys src/main.cpp src/database.cpp)

find_package(SQLite3 REQUIRED)
target_link_libraries(doc_sys SQLite::SQLite3)

add_executable(test_db tests/test_database.cpp src/database.cpp)
target_link_libraries(test_db SQLite::SQLite3)
add_test(NAME DatabaseTest COMMAND test_db)

# Install rules
install(TARGETS doc_sys DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

# Packaging configuration
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "DocumentationSystemGT")
set(CPACK_PACKAGE_VENDOR "Documentation System GT")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Documentation System for CRM case documentation")
set(CPACK_PACKAGE_VERSION "0.1.0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "DocumentationSystemGT")
if(WIN32)
  set(CPACK_GENERATOR "WIX")
  # Replace with a stable GUID when packaging for production
  set(CPACK_WIX_UPGRADE_GUID "12345678-1234-1234-1234-123456789abc")
endif()
include(CPack)

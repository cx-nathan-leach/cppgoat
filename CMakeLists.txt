cmake_minimum_required(VERSION 3.23)
project(cppgoat)

add_executable(cppgoat)
add_subdirectory(DAL)


target_sources(cppgoat PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/main.cc")
target_include_directories(cppgoat PUBLIC  "${CMAKE_SOURCE_DIR}/include")

find_package(httplib REQUIRED)
find_package(argparse REQUIRED)

target_link_libraries(cppgoat httplib::httplib argparse::argparse dalfactory)


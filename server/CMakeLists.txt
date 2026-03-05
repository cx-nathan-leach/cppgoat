cmake_minimum_required(VERSION 3.23)
project(server)

add_library(server STATIC server.cc)

find_package(httplib REQUIRED)
find_package(cpp-jwt REQUIRED)
find_package(Boost REQUIRED)

target_include_directories(server 
  PUBLIC  
    "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(server httplib::httplib cpp-jwt::cpp-jwt Boost::boost)


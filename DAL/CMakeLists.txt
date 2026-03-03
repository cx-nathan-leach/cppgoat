cmake_minimum_required(VERSION 3.23)
project(dalfactory)

add_library(dalfactory STATIC dalfactory.cc)

target_include_directories(dalfactory 
  PUBLIC  
    "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(dalfactory)


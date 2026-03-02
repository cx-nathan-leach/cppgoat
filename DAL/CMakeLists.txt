cmake_minimum_required(VERSION 3.23)
project(dalfactory)

add_subdirectory(sqlite)

add_library(dalfactory STATIC dalfactory.cc)

target_include_directories(dalfactory 
  PUBLIC  
    "${CMAKE_SOURCE_DIR}/include"
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/sqlite")

target_link_libraries(dalfactory sqlitedal)


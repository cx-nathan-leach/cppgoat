cmake_minimum_required(VERSION 3.23)
project(sqlitedal)

find_package(SQLite3 REQUIRED)

add_library(sqlitedal STATIC sqlitedal.cc)
target_link_libraries(sqlitedal SQLite::SQLite3)

target_include_directories(sqlitedal PUBLIC "${CMAKE_SOURCE_DIR}/include")

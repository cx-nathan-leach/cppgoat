cmake_minimum_required(VERSION 3.23)
project(sqlitedal)

find_package(SQLite3 REQUIRED)

add_library(sqlitedal SHARED sqlitedal.cc)
set_property(TARGET sqlitedal PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(sqlitedal SQLite::SQLite3)
target_include_directories(sqlitedal PUBLIC "${CMAKE_SOURCE_DIR}/include")

install(TARGETS sqlitedal)
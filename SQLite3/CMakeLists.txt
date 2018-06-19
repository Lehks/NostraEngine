cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(sqlite3 C)

add_library(sqlite3 SHARED sqlite3.c)

target_include_directories(sqlite3 PUBLIC ".")

target_compile_definitions(sqlite3 PUBLIC NOU_SQLITE3_EXPORT)
target_compile_definitions(sqlite3 PUBLIC NOU_SQLITE3_EXPORT_BUILD)

install(TARGETS sqlite3 DESTINATION bin)
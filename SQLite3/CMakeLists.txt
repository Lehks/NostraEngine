cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(SQLITE3 C)

add_definitions(-DNOU_SQLITE3_EXPORT)
add_definitions(-DNOU_SQLITE3_EXPORT_BUILD)

add_library("${NOE_SQLITE3_LIB_NAME}" SHARED "sqlite3.c")

install(TARGETS "${NOE_SQLITE3_LIB_NAME}" DESTINATION "bin")
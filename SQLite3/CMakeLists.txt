cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(sqlite3 C)

add_library(sqlite3 SHARED sqlite3.c)

#the sqlite3.h is contained within the sqlite3.c, therefore INTERFACE is enough
target_include_directories(sqlite3 INTERFACE "include")

target_compile_definitions(sqlite3 PUBLIC NOU_SQLITE3_EXPORT)
target_compile_definitions(sqlite3 PUBLIC NOU_SQLITE3_EXPORT_BUILD)

install(TARGETS sqlite3 
	RUNTIME DESTINATION "bin"
	LIBRARY DESTINATION "lib"
	ARCHIVE DESTINATION "lib"
	INCLUDES DESTINATION "include")
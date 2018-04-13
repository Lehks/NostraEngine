cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(SQLITE3 C)

add_library("${NOE_SQLITE3_LIB_NAME}" SHARED "sqlite3.c")
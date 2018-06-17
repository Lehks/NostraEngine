cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

find_package(Threads)

file(GLOB_RECURSE NOU_SOURCE_FILES "src/source/nostrautils/*.cpp")

include_directories("${NOE_NOU_INCLUDE_DIR}")

add_library("${NOE_NOU_DBG_LIB_NAME}" SHARED "${NOU_SOURCE_FILES}")

target_compile_definitions("${NOE_NOU_DBG_LIB_NAME}" PUBLIC -DNOU_DEBUG)

target_link_libraries("${NOE_NOU_DBG_LIB_NAME}" "${CMAKE_THREAD_LIBS_INIT}")

install(TARGETS "${NOE_NOU_DBG_LIB_NAME}" DESTINATION "bin")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")

	include_directories("${NOE_NOU_INCLUDE_DIR}")

	add_library("${NOE_NOU_LIB_NAME}" SHARED "${NOU_SOURCE_FILES}")
	
	target_link_libraries("${NOE_NOU_LIB_NAME}" "${CMAKE_THREAD_LIBS_INIT}")
	
	install(TARGETS "${NOE_NOU_LIB_NAME}" DESTINATION "bin")

endif()

# Append / to avoid having installed src/header instead of src/header/nostrautils
install(DIRECTORY "${NOE_NOU_INCLUDE_DIR}/" DESTINATION "include")
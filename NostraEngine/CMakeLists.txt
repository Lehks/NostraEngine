cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

project("${NOE_PROJECT_NAME}" 
	VERSION "${NOE_PROJECT_VERSION}"
	DESCRIPTION "${NOE_PROJECT_DESCRIPTION}"
	#HOMEPAGE_URL "${NOE_PROJECT_HOMEPAGE}" 
	LANGUAGES C CXX)

add_subdirectory("doc")

file(GLOB_RECURSE NOE_NOE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/NostraEngine/src/source/nostraengine/*.cpp")

include_directories("${NOE_NOE_INCLUDE_DIR}")
include_directories("${NOE_GLAD_INCLUDE_DIR}")
include_directories("${NOE_NOU_INCLUDE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}")

add_library("${NOE_NOE_DBG_LIB_NAME}" SHARED "${NOE_NOE_SOURCE_FILES}")

target_compile_definitions("${NOE_NOE_DBG_LIB_NAME}" PUBLIC -DNOU_DEBUG)

target_link_libraries("${NOE_NOE_DBG_LIB_NAME}" "${NOE_GLAD_LIB_NAME}")
target_link_libraries("${NOE_NOE_DBG_LIB_NAME}" "${NOE_SQLITE3_LIB_NAME}")
target_link_libraries("${NOE_NOE_DBG_LIB_NAME}" "${NOE_NOU_DBG_LIB_NAME}")

add_dependencies("${NOE_NOE_DBG_LIB_NAME}" "${NOE_GLAD_LIB_NAME}")
add_dependencies("${NOE_NOE_DBG_LIB_NAME}" "${NOE_SQLITE3_LIB_NAME}")
add_dependencies("${NOE_NOE_DBG_LIB_NAME}" "${NOE_NOU_DBG_LIB_NAME}")

install(TARGETS "${NOE_NOE_DBG_LIB_NAME}" DESTINATION "${NOE_BINARY_INSTALL_DIR}")
	
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")

	include_directories("${NOE_NOE_INCLUDE_DIR}")
	include_directories("${NOE_GLAD_INCLUDE_DIR}")
	include_directories("${NOE_NOU_INCLUDE_DIR}")
	include_directories("${CMAKE_SOURCE_DIR}")
	
	add_library("${NOE_NOE_LIB_NAME}" SHARED "${NOE_NOE_SOURCE_FILES}")
	
	target_link_libraries("${NOE_NOE_LIB_NAME}" "${NOE_GLAD_LIB_NAME}")
	target_link_libraries("${NOE_NOE_LIB_NAME}" "${NOE_SQLITE3_LIB_NAME}")
	target_link_libraries("${NOE_NOE_LIB_NAME}" "${NOE_NOU_LIB_NAME}")
	
	add_dependencies("${NOE_NOE_LIB_NAME}" "${NOE_GLAD_LIB_NAME}")
	add_dependencies("${NOE_NOE_LIB_NAME}" "${NOE_SQLITE3_LIB_NAME}")
	add_dependencies("${NOE_NOE_LIB_NAME}" "${NOE_NOU_LIB_NAME}")

	install(TARGETS "${NOE_NOE_LIB_NAME}" DESTINATION "${NOE_BINARY_INSTALL_DIR}")

endif()

install(DIRECTORY "${NOE_NOE_INCLUDE_DIR}/" DESTINATION "${NOE_INCLUDE_INSTALL_DIR}")
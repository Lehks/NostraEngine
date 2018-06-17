cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

project(TestPlugin CXX)

# Set language standard
if ("${NOE_CPP14_COMPATIBLILTY_MODE}")
	set (CMAKE_CXX_STANDARD 14)
	add_definitions(-DNOU_CPP14_COMPATIBILITY)
else()
	set (CMAKE_CXX_STANDARD 17)
endif()

#=== Add flags for debugging
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	add_definitions (-DNOU_DEBUG)
endif()
#===

set(TARGET_NAME TestPlugin2)

file(GLOB_RECURSE "files" "src/*.cpp")

include_directories("${NOE_NOE_INCLUDE_DIR}")
include_directories("${NOE_NOU_INCLUDE_DIR}")
include_directories("${CMAKE_SOURCE_DIR}")

add_definitions(-DNOE_PLUGIN)

add_library("${TARGET_NAME}" SHARED "${files}" "TestPluginPlugin2.cpp")

target_link_libraries("${TARGET_NAME}" "${NOE_NOU_LIB_NAME}")
target_link_libraries("${TARGET_NAME}" "${NOE_NOE_LIB_NAME}")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	add_dependencies("${TARGET_NAME}" "${NOE_NOU_DBG_LIB_NAME}")
endif()

set_target_properties("${TARGET_NAME}" PROPERTIES PREFIX "")
set_target_properties("${TARGET_NAME}" PROPERTIES SUFFIX ".np")

install(TARGETS "${TARGET_NAME}" 
	RUNTIME DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}" 
	LIBRARY DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
install(FILES "${TARGET_NAME}.pconf" DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")




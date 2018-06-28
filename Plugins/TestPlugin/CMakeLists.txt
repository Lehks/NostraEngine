cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

project(TestPlugin CXX)

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(TestPlugin SHARED "${files}" "TestPluginPlugin.cpp")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_link_libraries(TestPlugin 
		PRIVATE 
			NostraEngineDbg)
else()
	target_link_libraries(TestPlugin 
		PRIVATE 
			NostraEngine)
endif()

target_compile_definitions(TestPlugin 
	PRIVATE
		NOE_PLUGIN)

set_target_properties(TestPlugin PROPERTIES PREFIX "")
set_target_properties(TestPlugin PROPERTIES SUFFIX ".np")

install(TARGETS TestPlugin
	RUNTIME DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}" 
	LIBRARY DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
install(FILES "TestPlugin.pconf" DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")

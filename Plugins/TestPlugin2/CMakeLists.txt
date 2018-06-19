cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

project(TestPlugin2 CXX)

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(TestPlugin2 SHARED "${files}" "TestPluginPlugin2.cpp")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_link_libraries(TestPlugin2 
		PRIVATE 
			NostraEngineDbg)
else()
	target_link_libraries(TestPlugin2 
		PRIVATE 
			NostraEngine)
endif()

target_compile_definitions(TestPlugin2 
	PRIVATE
		NOE_PLUGIN)

set_target_properties(TestPlugin2 PROPERTIES PREFIX "")
set_target_properties(TestPlugin2 PROPERTIES SUFFIX ".np")

install(TARGETS TestPlugin2
	RUNTIME DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}" 
	LIBRARY DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
install(FILES "TestPlugin2.pconf" DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")




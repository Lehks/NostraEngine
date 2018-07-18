cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

project(TestPlugin CXX)

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(TestPlugin SHARED "${files}" "TestPluginPlugin.cpp")

target_link_libraries(TestPlugin 
	PRIVATE 
		Nostra::Engine)

target_compile_definitions(TestPlugin 
	PRIVATE
		NOE_PLUGIN)

set_target_properties(TestPlugin PROPERTIES PREFIX "")
set_target_properties(TestPlugin PROPERTIES SUFFIX ".np")

install(TARGETS TestPlugin
	RUNTIME DESTINATION "bin/plugins" 
	LIBRARY DESTINATION "bin/plugins")
install(FILES "TestPlugin.pconf" DESTINATION "bin/plugins")

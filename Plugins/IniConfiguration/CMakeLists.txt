cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

project(IniConfiguration CXX)

file(GLOB_RECURSE "files" "src/*.cpp")

add_library(IniConfiguration SHARED "${files}" "IniConfigurationPlugin.cpp")

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_link_libraries(IniConfiguration 
		PRIVATE 
			NostraEngineDbg)
else()
	target_link_libraries(IniConfiguration 
		PRIVATE 
			NostraEngine)
endif()

target_compile_definitions(IniConfiguration 
	PRIVATE
		NOE_PLUGIN)

set_target_properties(IniConfiguration PROPERTIES PREFIX "")
set_target_properties(IniConfiguration PROPERTIES SUFFIX ".np")

install(TARGETS IniConfiguration
	RUNTIME DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}" 
	LIBRARY DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")
install(FILES "IniConfiguration.pconf" DESTINATION "${NOE_PLUGIN_INSTALL_PREFIX}")

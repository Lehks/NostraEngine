cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

#=== Install directory for default-plugins
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set(NOE_PLUGIN_INSTALL_PREFIX "bin/plugins")
else()
	set(NOE_PLUGIN_INSTALL_PREFIX "plugins")
endif()
#===

add_subdirectory("GLFWWindow")
add_subdirectory("TestPlugin")
add_subdirectory("IniConfiguration")

cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

option(NOE_CPP14_COMPATIBLILTY_MODE "Disables some C++17-only features." OFF)
option(NOE_GENERATE_DOC "Generate Doxygen-Documentation." ON)

message(STATUS "${CMAKE_BUILD_TYPE}")

if((NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Debug") AND (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "Release"))
	
	message(FATAL_ERROR "An invalid build type was passed. The allowed types are: \"Debug\" or \"Release\"")

endif()

#=== Project Metadata
set(NOE_PROJECT_NAME        "NostraEngine")
set(NOE_PROJECT_VERSION     "0.0.1")
set(NOE_PROJECT_DESCRIPTION "A real-time game engine.")
set(NOE_PROJECT_ICON        "")
set(NOE_PROJECT_LICENSE     "LICENSE.md")
set(NOE_PROJECT_CREATORS    "The Nostra Project Team")
set(NOE_PROJECT_HOMEPAGE    "https://www.github.com/Lehks/NostraEngine")
#===

# Set language standard
if ("${NOE_CPP14_COMPATIBLILTY_MODE}")
	set (CMAKE_CXX_STANDARD 14)
	message(STATUS "NOE:  Generating for C++14 compatibility mode.")
	add_definitions(-DNOU_CPP14_COMPATIBILITY)
else()
	set (CMAKE_CXX_STANDARD 17)
	message(STATUS "NOE:  Generating without C++14 compatibility mode.")
endif()

#=== Set RPATH
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${NOE_BINARY_INSTALL_DIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#===

#=== Set stdlib++ for AppleClang
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
	add_definitions("-stdlib=libc++ -lc++experimental")
endif()
#===

#=== Variables for NostraEngine target
set(NOE_EXECUTABLE "NostraEngineExe")
set(NOE_EXECUTABLE_SOURCE "main.cpp")
#===

#=== Variables for Test target
set(NOE_TEST_EXECUTABLE "Test")
set(NOE_TEST_EXECUTABLE_SOURCE "testmain.cpp")
set(NOE_TEST_EXECUTABLE_SOURCE_TEMPLATE "testmain.cpp.in")
#===

#=== Install directory for default-plugins
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	set(NOE_PLUGIN_INSTALL_PREFIX "bin/plugins")
else()
	set(NOE_PLUGIN_INSTALL_PREFIX "plugins")
endif()
#===

#Build GLAD
add_subdirectory("GLAD")

#Build SQLite3
add_subdirectory("SQLite3")

#Build Nostra Engine
add_subdirectory("NostraEngine")

#Build Nostra Utils
add_subdirectory("NostraUtils")

#Build Plugins
add_subdirectory("Plugins")


#=== Debug-Build (with Test and NostraEngineExe)
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")

	message(STATUS "NOE:  Building in Debug mode, Test-executables will be generated.")

	#=== Build NostraEngine target
	add_executable("${NOE_EXECUTABLE}" "${NOE_EXECUTABLE_SOURCE}")
	
	target_link_libraries("${NOE_EXECUTABLE}" "${NOE_NOU_DBG_LIB_NAME}")
	
	install(TARGETS "${NOE_EXECUTABLE}" DESTINATION "bin")
	#===
	
	#=== Build Test target
	#Create testmain.cpp if it does not exist
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/${NOE_TEST_EXECUTABLE_SOURCE}")
		configure_file("${CMAKE_SOURCE_DIR}/${NOE_TEST_EXECUTABLE_SOURCE_TEMPLATE}" 
								"${CMAKE_SOURCE_DIR}/${NOE_TEST_EXECUTABLE_SOURCE}")
		message(STATUS "NOE:  ${NOE_TEST_EXECUTABLE_SOURCE} was not found. A default one was generated.")
	endif()
	
	
	add_executable("${NOE_TEST_EXECUTABLE}" "${NOE_TEST_EXECUTABLE_SOURCE}")
	
	target_link_libraries("${NOE_TEST_EXECUTABLE}" PRIVATE "${NOE_NOE_DBG_LIB_NAME}")
	#=== 

else()

	message(STATUS "NOE:  Building in Release mode, no Test-executables will be generated.")
	
	set(CPACK_PACKAGE_NAME "${NOE_PROJECT_NAME}")
	set(CPACK_PACKAGE_VENDOR "${NOE_PROJECT_CREATORS}")
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${NOE_PROJECT_DESCRIPTION}")
	set(CPACK_PACKAGE_VERSION "${NOE_PROJECT_VERSION}")
	set(CPACK_PACKAGE_HOMEPAGE_URL "${NOE_PROJECT_HOMEPAGE}")
	set(CPACK_PACKAGE_INSTALL_DIRECTORY "${NOE_PROJECT_NAME}")
	#set(CPACK_PACKAGE_ICON "${NOE_PROJECT_ICON}")
	set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/${NOE_PROJECT_LICENSE}")
	set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
	
	include(CPack)
endif()

#Install license file
install(FILES "LICENSE.md" DESTINATION ".")

install(FILES "CHANGELOG.md" DESTINATION ".")

#=== Install readme
#=== Either install the Install-Readme or Debug-Readme
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
	install(TARGETS "${NOE_TEST_EXECUTABLE}" DESTINATION "bin")
else()
	#Install README.md
	configure_file("INSTALL_README.md.in" "INSTALL_README.md")
	install(FILES "${CMAKE_BINARY_DIR}/INSTALL_README.md" DESTINATION "." RENAME "README.md")
endif()
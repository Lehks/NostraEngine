cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

option(NOE_CPP14_COMPATIBLILTY_MODE "Disables some C++17-only features." OFF)
option(NOE_GENERATE_DOC "Generate Doxygen-Documentation." ON)

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
	add_executable(NostraEngineExe main.cpp)
	
	target_link_libraries(NostraEngineExe 
		PRIVATE
			NostraEngineDbg)
	
	install(TARGETS NostraEngineExe DESTINATION bin)
	#===
	
	#=== Build Test target
	#Create testmain.cpp if it does not exist
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/testmain.cpp")
		message(WARNING "NOE:  testmain.cpp was not found. NostraEngineTest will not be generated.")
	else()
		message(STATUS "NOE:  testmain.cpp was found. NostraEngineTest will be generated.")
		add_executable(NostraEngineTest testmain.cpp)
	
		target_link_libraries(NostraEngineTest 
			PRIVATE 
				NostraEngineDbg)
	endif()
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
	if(TARGET NostraEngineTest)
		install(TARGETS NostraEngineTest DESTINATION bin)
	endif()
else()
	#Install README.md
	configure_file("INSTALL_README.md.in" "INSTALL_README.md")
	install(FILES "${CMAKE_BINARY_DIR}/INSTALL_README.md" DESTINATION "." RENAME "README.md")
endif()
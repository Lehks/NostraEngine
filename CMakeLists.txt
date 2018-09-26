cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

option(NOE_GENERATE_TEST_EXECUTABLE "Generate the target NostraEngineTest." OFF)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	if(UNIX)
		set(CMAKE_INSTALL_PREFIX "/opt/NostraEngine" CACHE PATH 
											"Install path prefix, prepended onto install directories." FORCE)
	elseif(WIN32)
		set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/NostraEngine" CACHE PATH 
											"Install path prefix, prepended onto install directories." FORCE)
	endif()
endif()

#Build GLAD
add_subdirectory("GLAD")

#Build SQLite3
add_subdirectory("SQLite3")

#Build Flex/Bison
add_subdirectory("materialcompiler")

#Build Nostra Utils
add_subdirectory("NostraUtils")

#Build Nostra Engine
add_subdirectory("NostraEngine")

#Build Plugins
add_subdirectory("Plugins")

#=== Build NostraEngineExe target
add_executable(NostraEngineExe main.cpp)

target_link_libraries(NostraEngineExe 
	PRIVATE
		Nostra::Engine)

install(TARGETS NostraEngineExe 
	DESTINATION bin)
#===

#=== Build Test target
if(${NOE_GENERATE_TEST_EXECUTABLE})
	if(NOT EXISTS "${CMAKE_SOURCE_DIR}/testmain.cpp")
		message(WARNING "NOE:  testmain.cpp was not found. No Test-Executable will be generated.")
	else()
		add_executable(NostraEngineTest testmain.cpp)

		target_link_libraries(NostraEngineTest 
			PRIVATE 
				Nostra::Engine)

		if(GENERATE_FLEX_BISON)
			target_link_libraries(NostraEngineTest
				PRIVATE
					NostraEngineCompiler)
		endif()

		install(TARGETS NostraEngineTest 
				DESTINATION bin)
	endif()
endif()
#=== 

install(FILES "LICENSE.md" DESTINATION ".")
install(FILES "CHANGELOG.md" DESTINATION ".")

#Install README.md
configure_file("INSTALL_README.md.in" "INSTALL_README.md")
install(FILES "${CMAKE_BINARY_DIR}/INSTALL_README.md" DESTINATION "." RENAME "README.md")

if(${CMAKE_SYSTEM} MATCHES "Linux")
	#Install .conf file with path to .so files
	configure_file("cmake/nostraengine.conf.in" "nostraengine.conf" @ONLY)
	install(FILES "${CMAKE_BINARY_DIR}/nostraengine.conf" DESTINATION "/etc/ld.so.conf.d")
endif()

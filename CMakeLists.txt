cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

option(NOE_GENERATE_TEST_EXECUTABLE "Generate the target NostraEngineTest." OFF)

#Build GLAD
add_subdirectory("GLAD")

#Build SQLite3
add_subdirectory("SQLite3")

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
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/testmain.cpp")
	message(WARNING "NOE:  testmain.cpp was not found. No Test-Executable will be generated.")
else()
	add_executable(NostraEngineTest testmain.cpp)

	target_link_libraries(NostraEngineTest 
		PRIVATE 
			Nostra::Engine)
		
	install(TARGETS NostraEngineTest 
			DESTINATION bin)
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

	#Install uninstall script and required file(s)
	install(FILES "${CMAKE_BINARY_DIR}/install_manifest.txt" DESTINATION ".")
	configure_file("cmake/uninstall.in" "uninstall" COPYONLY)
	install(FILES "${CMAKE_BINARY_DIR}/uninstall" 
		PERMISSIONS
			OWNER_WRITE
			OWNER_READ
			OWNER_EXECUTE
			GROUP_READ
			GROUP_EXECUTE
			WORLD_READ
			WORLD_EXECUTE
		DESTINATION 
			".")
	install()
endif()

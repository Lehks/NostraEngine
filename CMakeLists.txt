cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

option(NOE_GENERATE_TEST_EXECUTABLE "")

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
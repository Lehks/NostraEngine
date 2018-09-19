cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

option(NOE_GENERATE_DOC "Generate Doxygen-Documentation." ON)

if(${NOE_GENERATE_DOC})
	
	message(STATUS "NOE:  Attempting to generate Doxygen-Doc.")

	find_package(Doxygen OPTIONAL_COMPONENTS dot)

	if(${DOXYGEN_FOUND})

		message(STATUS "NOE:  Doxygen-Executable was found, Doc will be generated.")

		configure_file(Doxyfile.in Doxyfile @ONLY)



		add_custom_target("Documentation" 
			ALL COMMAND Doxygen::doxygen "Doxyfile"
			WORKING_DIRECTORY "."
			COMMENT "Generating Doxygen-Documentation"
			VERBATIM)

		install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION "doc")

	else()
	
		message(WARNING "NOE:  Doxygen-Executable could not be found, Doc generation will be omitted.")

	endif()
	
endif()
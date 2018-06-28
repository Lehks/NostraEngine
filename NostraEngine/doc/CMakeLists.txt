cmake_minimum_required(VERSION 3.8.3 FATAL_ERROR)

if(${NOE_GENERATE_DOC})
	
	message(STATUS "NOE:  Attempting to generate Doxygen-Doc.")

	find_package(Doxygen OPTIONAL_COMPONENTS dot)

	if(${DOXYGEN_FOUND})
		
		message(STATUS "NOE:  Doxygen-Executable was found, Doc will be generated.")

		set(NOE_DOXYFILE_IN "Doxyfile.in")
		set(NOE_DOXYFILE    "Doxyfile")

		configure_file("${NOE_DOXYFILE_IN}" "${NOE_DOXYFILE}" @ONLY)



		add_custom_target("${NOE_DOC_TARGET}" 
			ALL COMMAND "${DOXYGEN_EXECUTABLE}" "${NOE_DOXYFILE}"
			WORKING_DIRECTORY "."
			COMMENT "Generating Doxygen-Documentation"
			VERBATIM)

		install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html/" DESTINATION "${NOE_DOC_INSTALL_DIR}")

	else()
	
		message(WARNING "NOE:  Doxygen-Executable could not be found, Doc generation will be omitted.")

	endif()
	
endif()
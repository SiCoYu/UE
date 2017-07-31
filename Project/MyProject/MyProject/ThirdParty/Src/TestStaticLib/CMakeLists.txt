project(TestStaticLib)

# 只处理 win32 平台  
if(WIN32)
	message(STATUS "TestStaticLib Project")
	
	set(SRCS
		./TestStaticLibA.cpp
		./TestStaticLibB.cpp
	)

	set(INCS
		./TestStaticLibA.h
		./TestStaticLibB.h
	)

	source_group("Source Files" FILES ${SRCS} ${INCS})

	if (CMAKE_BUILD_TYPE STREQUAL Debug)
		add_definitions(-DNDEBUG)
	endif ()
	
	if (MSVC)
		set(CompilerFlags
			CMAKE_CXX_FLAGS
			CMAKE_CXX_FLAGS_DEBUG
			CMAKE_CXX_FLAGS_RELEASE
			CMAKE_CXX_FLAGS_MINSIZEREL
			CMAKE_CXX_FLAGS_RELWITHDEBINFO
			CMAKE_C_FLAGS
			CMAKE_C_FLAGS_DEBUG
			CMAKE_C_FLAGS_RELEASE
			)
		foreach(CompilerFlag ${CompilerFlags})
			string(REPLACE "/MDd" "/MD" ${CompilerFlag} "${${CompilerFlag}}")
		endforeach()
	endif()
	
	if (MSVC)
		set(CompilerFlags
			CMAKE_CXX_FLAGS_DEBUG
			)
		foreach(CompilerFlag ${CompilerFlags})
			string(REPLACE "_DEBUG" "NDEBUG" ${CompilerFlag} "${${CompilerFlag}}")
		endforeach()
	endif()
	
    include_directories(.)
    ADD_LIBRARY(TestStaticLib STATIC ${SRCS} ${INCS})
	set_target_properties(TestStaticLib PROPERTIES DEBUG_POSTFIX _d)
	
	#SET(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../Lib/${PROJECT_NAME}")
	
	file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}")
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}")
	
	install(FILES 
		${CMAKE_CURRENT_SOURCE_DIR}/TestStaticLibA.h
		${CMAKE_CURRENT_SOURCE_DIR}/TestStaticLibB.h
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}"
	)
	
	file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}")
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}")
	
	install(FILES 
		${TestStaticLib_BINARY_DIR}/Debug/TestStaticLib_d.lib
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}" CONFIGURATIONS Debug
	)
	install(FILES 
		${TestStaticLib_BINARY_DIR}/Release/TestStaticLib.lib
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}" CONFIGURATIONS Release None ""
	)
	install(FILES 
		${TestStaticLib_BINARY_DIR}/RelWithDebInfo/TestStaticLib.lib
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}" CONFIGURATIONS RelWithDebInfo
	)
	install(FILES 
		${TestStaticLib_BINARY_DIR}/MinSizeRel/TestStaticLib.lib
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}" CONFIGURATIONS MinSizeRel
	)
	
endif(WIN32)
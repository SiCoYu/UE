project(Sockets_Test)

# 只处理 win32 平台  
if(WIN32)
	message(STATUS "Sockets Project")
	
	set(Test_SRCS
		./sockets_test.cpp
	)

	source_group("Source Files" FILES ${Test_SRCS})

	set(SRCS ${Test_SRCS})
	
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
	
    include_directories(..)
	ADD_EXECUTABLE(Sockets_Test WIN32 ${SRCS})
	set_target_properties(Sockets_Test PROPERTIES DEBUG_POSTFIX _d LINK_FLAGS "/ENTRY:\"mainCRTStartup\"")
	TARGET_LINK_LIBRARIES(Sockets_Test Sockets)
	
endif(WIN32)
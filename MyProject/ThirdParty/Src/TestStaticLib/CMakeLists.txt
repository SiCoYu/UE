project(TestStaticLib)

# 只处理 win32 平台  
if(WIN32)
	message(STATUS "TestStaticLib Project")
	
	set(SRCS
		./TestStaticLib.cpp
	)

	set(INCS
		./TestStaticLib.h
	)

	source_group("Source Files" FILES ${SRCS} ${INCS})

    include_directories(.)
    ADD_LIBRARY(TestStaticLib STATIC ${SRCS} ${INCS})
	set_target_properties(TestStaticLib PROPERTIES DEBUG_POSTFIX _d)
	
	file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}")
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}")
	
	SET(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../Lib/${PROJECT_NAME}")
	
	file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}")
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}")
	
	install(FILES 
		${CMAKE_CURRENT_SOURCE_DIR}/TestStaticLib.h
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}"
	)
	
endif(WIN32)
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
	
	#SET(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../Lib/${PROJECT_NAME}")
	
	file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}")
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}")
	
	install(FILES 
		${CMAKE_CURRENT_SOURCE_DIR}/TestStaticLib.h
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
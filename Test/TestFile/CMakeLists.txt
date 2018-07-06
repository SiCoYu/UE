project(TestPort)

cmake_minimum_required(VERSION 2.8.10)

file(GLOB SRCS_App_FILES Src/App/*.h Src/App/*.cpp)
source_group("Src\\App" FILES ${SRCS_App_FILES})

IF(WIN32)
	file(GLOB SRCS_PlatformDepend_FILES Src/Windows/*.h Src/Windows/*.cpp)
	source_group("Src\\Windows" FILES ${SRCS_PlatformDepend_FILES})
	
	add_definitions(-DPLATFORM_WINDOWS)
ELSEIF(APPLE)

ELSEIF(UNIX)

ELSEIF(LINUX)

ENDIF()

include_directories(Src Src/App)

IF(DEBUG_mode)
    add_definitions(-DDEBUG)
ENDIF()

#ADD_DEFINITIONS(-DTEST)

set(ALL_SRCS ${SRCS_App_FILES})

ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${ALL_SRCS})

#SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX LINK_FLAGS "/SUBSYSTEM:\"CONSOLE\"")
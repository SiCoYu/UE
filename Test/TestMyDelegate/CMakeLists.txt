project(TestMyDelegate)

cmake_minimum_required(VERSION 2.8.10)

file(GLOB SRCS_App_FILES Src/App/*.h Src/App/*.cpp)
source_group("Src\\App" FILES ${SRCS_App_FILES})

file(GLOB SRCS_MyDelegate_FILES Src/MyDelegate/*.h Src/MyDelegate/*.cpp)
source_group("Src\\MyDelegate" FILES ${SRCS_MyDelegate_FILES})

file(GLOB SRCS_Templates_FILES Src/Templates/*.h Src/Templates/*.cpp)
source_group("Src\\Templates" FILES ${SRCS_Templates_FILES})

IF(WIN32)
	add_definitions(-DPLATFORM_WINDOWS)
ELSEIF(APPLE)

ELSEIF(UNIX)

ELSEIF(LINUX)

ENDIF()

include_directories(Src Src/App Src/MyDelegate)

IF(DEBUG_mode)
    add_definitions(-DDEBUG)
ENDIF()

#ADD_DEFINITIONS(-DTEST)

set(ALL_SRCS ${SRCS_App_FILES} ${SRCS_MyDelegate_FILES} ${SRCS_Templates_FILES})

ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${ALL_SRCS})

#SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX LINK_FLAGS "/SUBSYSTEM:\"CONSOLE\"")
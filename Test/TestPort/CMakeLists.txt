project(TestPort)

cmake_minimum_required(VERSION 2.8.10)

file(GLOB SRCS_FILES Src/*.h Src/*.cpp)
source_group("SourceFiles" FILES ${SRCS_FILES})

include_directories(./Src)
set(ALLSRCS ${SRCS_FILES})

ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${ALLSRCS})
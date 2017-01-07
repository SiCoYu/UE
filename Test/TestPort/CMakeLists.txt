project(TestPort)

cmake_minimum_required(VERSION 2.8.10)

file(GLOB SRCS_Templates_FILES Src/Templates/*.h Src/Templates/*.cpp)
source_group("Src/Templates" FILES ${SRCS_Templates_FILES})

file(GLOB SRCS_Traits_FILES Src/Traits/*.h Src/Traits/*.cpp)
source_group("Src/Traits" FILES ${SRCS_Traits_FILES})

file(GLOB SRCS_App_FILES Src/App/*.h Src/App/*.cpp)
source_group("Src/App" FILES ${SRCS_App_FILES})

file(GLOB SRCS_Test_FILES Src/Test/*.h Src/Test/*.cpp)
source_group("Src/Test" FILES ${SRCS_Test_FILES})

include_directories(./Src)
set(ALLSRCS ${SRCS_Templates_FILES} ${SRCS_Traits_FILES} ${SRCS_App_FILES} ${SRCS_Test_FILES})

ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${ALLSRCS})
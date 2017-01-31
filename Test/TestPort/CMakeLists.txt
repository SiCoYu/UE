project(TestPort)

cmake_minimum_required(VERSION 2.8.10)

file(GLOB SRCS_Templates_FILES Src/Templates/*.h Src/Templates/*.cpp)
source_group("Src\\Templates" FILES ${SRCS_Templates_FILES})

file(GLOB SRCS_Traits_FILES Src/Traits/*.h Src/Traits/*.cpp)
source_group("Src\\Traits" FILES ${SRCS_Traits_FILES})

file(GLOB SRCS_App_FILES Src/App/*.h Src/App/*.cpp)
source_group("Src\\App" FILES ${SRCS_App_FILES})

file(GLOB SRCS_Test_FILES Src/Test/*.h Src/Test/*.cpp)
source_group("Src\\Test" FILES ${SRCS_Test_FILES})

file(GLOB SRCS_GenericPlatform_FILES Src/GenericPlatform/*.h Src/GenericPlatform/*.cpp)
source_group("Src\\GenericPlatform" FILES ${SRCS_GenericPlatform_FILES})

file(GLOB SRCS_HAL_FILES Src/HAL/*.h Src/HAL/*.cpp)
source_group("Src\\HAL" FILES ${SRCS_HAL_FILES})

file(GLOB SRCS_Math_FILES Src/Math/*.h Src/Math/*.cpp)
source_group("Src\\Math" FILES ${SRCS_Math_FILES})

file(GLOB SRCS_Logging_FILES Src/Logging/*.h Src/Logging/*.cpp)
source_group("Src\\Logging" FILES ${SRCS_Logging_FILES})

file(GLOB SRCS_Misc_FILES Src/Misc/*.h Src/Misc/*.cpp)
source_group("Src\\Misc" FILES ${SRCS_Misc_FILES})

file(GLOB SRCS_Containers_FILES Src/Containers/*.h Src/Containers/*.cpp)
source_group("Src\\Containers" FILES ${SRCS_Containers_FILES})

include_directories(Src Src/Templates Src/Traits Src/App Src/Test Src/GenericPlatform Src/HAL Src/Math Src/Logging Src/Misc Src/Containers)
set(ALL_SRCS ${SRCS_Templates_FILES} ${SRCS_Traits_FILES} ${SRCS_App_FILES} ${SRCS_Test_FILES} ${SRCS_GenericPlatform_FILES} ${SRCS_HAL_FILES} ${SRCS_Math_FILES} ${SRCS_Logging_FILES} ${SRCS_Misc_FILES} ${SRCS_Containers_FILES})

ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${ALL_SRCS})

#SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX LINK_FLAGS "/SUBSYSTEM:\"CONSOLE\"")
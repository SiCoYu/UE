cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0003 NEW)
cmake_policy(SET CMP0005 NEW)

project(ThirdParty)

message(STATUS "builder main start")

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})

if(MSVC)
	message(STATUS "Setting Visual Studio option")
	add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-DNOMINMAX)
endif(MSVC)

add_subdirectory(Sockets-2.3.9.9)
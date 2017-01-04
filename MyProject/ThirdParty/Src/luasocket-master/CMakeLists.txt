project(LuaSocket)

message(STATUS "${PROJECT_NAME} Project")
set(SRCS
	./src/auxiliar.h
	./src/auxiliar.c
	./src/buffer.h
	./src/buffer.c
	./src/except.h
	./src/except.c
	./src/inet.h
	./src/inet.c
	./src/io.h
	./src/io.c
	./src/luasocket.h
	./src/luasocket.c
	./src/options.h
	./src/options.c
	./src/select.h
	./src/select.c
	./src/tcp.h
	./src/tcp.c
	./src/timeout.h
	./src/timeout.c
	./src/udp.h
	./src/udp.c
	./src/wsocket.h
	./src/wsocket.c
	
	./src/mime.h
	./src/mime.c
)

source_group("Src" FILES ${SRCS})

set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")  

include_directories(./src ../lua-5.3.1/src)
link_directories(../../Lib/Lua)

ADD_LIBRARY(${PROJECT_NAME} STATIC ${SRCS})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX _d)

# ¿½±´ÎÄ¼þ
file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/../Inc/${PROJECT_NAME}")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/../Inc/${PROJECT_NAME}")

file(GLOB_RECURSE COPY_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
install(FILES ${COPY_SRC} DESTINATION "${CMAKE_SOURCE_DIR}/../Inc/${PROJECT_NAME}")

file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/../Lib/${PROJECT_NAME}")
file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/../Lib/${PROJECT_NAME}")

install(FILES 
	${CMAKE_CURRENT_BINARY_DIR}/Debug/${PROJECT_NAME}_d.lib
	DESTINATION "${CMAKE_SOURCE_DIR}/../Lib/${PROJECT_NAME}" CONFIGURATIONS Debug
)
install(FILES 
	${CMAKE_CURRENT_BINARY_DIR}/Release/${PROJECT_NAME}.lib
	DESTINATION "${CMAKE_SOURCE_DIR}/../Lib/${PROJECT_NAME}" CONFIGURATIONS Release None ""
)
install(FILES 
	${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo/${PROJECT_NAME}.lib
	DESTINATION "${CMAKE_SOURCE_DIR}/../Lib/${PROJECT_NAME}" CONFIGURATIONS RelWithDebInfo
)
install(FILES 
	${CMAKE_CURRENT_BINARY_DIR}/MinSizeRel/${PROJECT_NAME}.lib
	DESTINATION "${CMAKE_SOURCE_DIR}/../Lib/${PROJECT_NAME}" CONFIGURATIONS MinSizeRel
)
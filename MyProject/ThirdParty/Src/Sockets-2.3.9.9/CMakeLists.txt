project(Sockets)

# 只处理 win32 平台  
if(WIN32)
	message(STATUS "Sockets Project")
	set(AsynchronousDNS_SRCS
		./ResolvServer.cpp
		./ResolvSocket.cpp
	)

	set(AsynchronousDNS_INCS
		./ResolvServer.h
		./ResolvSocket.h
	)
	
	set(BasicSockets_SRCS
		./Ipv4Address.cpp
		./Ipv6Address.cpp
		./SctpSocket.cpp
		./Socket.cpp
		./SocketHandler.cpp
		./SocketHandlerThread.cpp
		./SocketThread.cpp
		./StreamSocket.cpp
		./TcpSocket.cpp
		./UdpSocket.cpp
	)

	set(BasicSockets_INCS
		./Ipv4Address.h
		./Ipv6Address.h
		./ISocketHandler.h
		./ListenSocket.h
		./SctpSocket.h
		./Socket.h
		./SocketHandler.h
		./SocketAddress.h
		./StreamSocket.h
		./SocketHandlerThread.h
		./SocketThread.h
		./TcpSocket.h
		./UdpSocket.h
	)
	
	set(Filehandling_SRCS
		./File.cpp
		./MemFile.cpp
	)

	set(Filehandling_INCS
		./File.h
		./IFile.h
		./MemFile.h
	)
	
	set(HeaderFiles_INCS
		./Exception.h
		./socket_include.h
		./sockets-config.h
	)
	
	set(HTTPSockets_SRCS
		./HttpClientSocket.cpp
		./HttpDebugSocket.cpp
		./HttpGetSocket.cpp
		./HttpPostSocket.cpp
		./HttpPutSocket.cpp
		./HTTPSocket.cpp
	)

	set(HTTPSockets_INCS
		./HttpClientSocket.h
		./HttpDebugSocket.h
		./HttpGetSocket.h
		./HttpPostSocket.h
		./HttpPutSocket.h
		./HTTPSocket.h
	)
	
	set(Internal_SRCS
		./SSLInitializer.cpp
	)

	set(Internal_INCS
		./SSLInitializer.h
	)
	
	set(Loghelpclasses_SRCS
		./StdoutLog.cpp
	)

	set(Loghelpclasses_INCS
		./StdLog.h
		./StdoutLog.h
	)
	
	set(SMTP_SRCS
		./SmtpdSocket.cpp
	)

	set(SMTP_INCS
		./SmtpdSocket.h
	)
	
	set(SourceFiles_SRCS
		./Exception.cpp
		./socket_include.cpp
	)

	set(Threading_SRCS
		./Lock.cpp
		./Mutex.cpp
		./Semaphore.cpp
		./Thread.cpp
	)

	set(Threading_INCS
		./Lock.h
		./Mutex.h
		./Semaphore.h
		./Thread.h
	)
	
	set(TimerEvents_SRCS
		./Event.cpp
		./EventHandler.cpp
		./EventTime.cpp
		./IEventOwner.cpp
	)

	set(TimerEvents_INCS
		./Event.h
		./EventHandler.h
		./EventTime.h
		./IEventHandler.h
		./IEventOwner.h
	)
	
	set(Utilities_SRCS
		./Base64.cpp
		./Debug.cpp
		./Parse.cpp
		./Utility.cpp
	)
	
	set(Utilities_INCS
		./Base64.h
		./Debug.h
		./Parse.h
		./Utility.h
	)
	
	set(Webserverframework_SRCS
		./Ajp13Socket.cpp
		./AjpBaseSocket.cpp
		./HttpBaseSocket.cpp
		./HttpdCookies.cpp
		./HttpdForm.cpp
		./HttpdSocket.cpp
		./HttpRequest.cpp
		./HttpResponse.cpp
		./HttpTransaction.cpp
	)

	set(Webserverframework_INCS
		./ajp13.h
		./Ajp13Socket.h
		./AjpBaseSocket.h
		./HttpBaseSocket.h
		./HttpdCookies.h
		./HttpdForm.h
		./HttpdSocket.h
		./HttpRequest.h
		./HttpResponse.h
		./HttpTransaction.h
		./IHttpServer.h
	)
	
	set(Xml_SRCS
		./XmlDocument.cpp
		./XmlException.cpp
		./XmlNode.cpp
	)

	set(Xml_INCS
		./XmlDocument.h
		./XmlException.h
		./XmlNode.h
	)

	source_group("Asynchronous DNS" FILES ${AsynchronousDNS_SRCS} ${AsynchronousDNS_INCS})
	source_group("Basic Sockets" FILES ${BasicSockets_SRCS} ${BasicSockets_INCS})
	source_group("File handling" FILES ${Filehandling_SRCS} ${Filehandling_INCS})
	source_group("Header Files" FILES ${HeaderFiles_INCS})
	source_group("HTTP Sockets" FILES ${HTTPSockets_SRCS} ${HTTPSockets_INCS})
	source_group("Internal" FILES ${Internal_SRCS} ${Internal_INCS})
	source_group("Log help classes" FILES ${Loghelpclasses_SRCS} ${Loghelpclasses_INCS})
	source_group("SMTP" FILES ${SMTP_SRCS} ${SMTP_INCS})
	source_group("Source Files" FILES ${SourceFiles_SRCS})
	source_group("Threading" FILES ${Threading_SRCS} ${Threading_INCS})
	source_group("Timer Events" FILES ${TimerEvents_SRCS} ${TimerEvents_INCS})
	source_group("Utilities" FILES ${Utilities_SRCS} ${Utilities_INCS})
	source_group("Webserver framework" FILES ${Webserverframework_SRCS} ${Webserverframework_INCS})
	source_group("Xml" FILES ${Xml_SRCS} ${Xml_INCS})

	set(SRCS ${AsynchronousDNS_SRCS} ${BasicSockets_SRCS} ${Filehandling_SRCS} ${HTTPSockets_SRCS} ${Internal_SRCS} ${Loghelpclasses_SRCS} ${SMTP_SRCS} ${SourceFiles_SRCS} ${Threading_SRCS} ${TimerEvents_SRCS} ${TimerEvents_SRCS} ${Utilities_SRCS} ${Webserverframework_SRCS} ${Xml_SRCS})
	set(INCS ${AsynchronousDNS_INCS} ${BasicSockets_INCS} ${Filehandling_INCS} ${HeaderFiles_INCS} ${HTTPSockets_INCS} ${Internal_INCS} ${Loghelpclasses_INCS} ${SMTP_INCS} ${Threading_INCS} ${TimerEvents_INCS} ${Utilities_INCS} ${Webserverframework_INCS} ${Xml_INCS})
	
    include_directories(.)
    ADD_LIBRARY(Sockets STATIC ${SRCS} ${INCS})
	set_target_properties(Sockets PROPERTIES DEBUG_POSTFIX _d)
	
	#SET(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../Lib/${PROJECT_NAME}")
	
	file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}")
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}")
	
	message(STATUS "aaa ${CMAKE_LIBRARY_ARCHITECTURE}")
	message(STATUS "bbb ${CMAKE_BUILD_TYPE}")
	
	install(FILES 
		${CMAKE_CURRENT_SOURCE_DIR}/ajp13.h
		${CMAKE_CURRENT_SOURCE_DIR}/Ajp13Socket.h
		${CMAKE_CURRENT_SOURCE_DIR}/AjpBaseSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/Base64.h
		${CMAKE_CURRENT_SOURCE_DIR}/Debug.h
		${CMAKE_CURRENT_SOURCE_DIR}/Event.h
		${CMAKE_CURRENT_SOURCE_DIR}/EventHandler.h
		${CMAKE_CURRENT_SOURCE_DIR}/EventTime.h
		${CMAKE_CURRENT_SOURCE_DIR}/Exception.h
		${CMAKE_CURRENT_SOURCE_DIR}/File.h
		${CMAKE_CURRENT_SOURCE_DIR}/FileStream.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpBaseSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpClientSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpdCookies.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpDebugSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpdForm.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpdSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpGetSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpPostSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpPutSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpRequest.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpResponse.h
		${CMAKE_CURRENT_SOURCE_DIR}/HTTPSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/HttpTransaction.h
		${CMAKE_CURRENT_SOURCE_DIR}/IBase.h
		${CMAKE_CURRENT_SOURCE_DIR}/IEventHandler.h
		${CMAKE_CURRENT_SOURCE_DIR}/IEventOwner.h
		${CMAKE_CURRENT_SOURCE_DIR}/IFile.h
		${CMAKE_CURRENT_SOURCE_DIR}/IFileUpload.h
		${CMAKE_CURRENT_SOURCE_DIR}/IHttpServer.h
		${CMAKE_CURRENT_SOURCE_DIR}/IModel.h
		${CMAKE_CURRENT_SOURCE_DIR}/IMutex.h
		${CMAKE_CURRENT_SOURCE_DIR}/Ipv4Address.h
		${CMAKE_CURRENT_SOURCE_DIR}/Ipv6Address.h
		${CMAKE_CURRENT_SOURCE_DIR}/ISocketHandler.h
		${CMAKE_CURRENT_SOURCE_DIR}/IStream.h
		${CMAKE_CURRENT_SOURCE_DIR}/Json.h
		${CMAKE_CURRENT_SOURCE_DIR}/ListenSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/Lock.h
		${CMAKE_CURRENT_SOURCE_DIR}/MemFile.h
		${CMAKE_CURRENT_SOURCE_DIR}/Mutex.h
		${CMAKE_CURRENT_SOURCE_DIR}/Parse.h
		${CMAKE_CURRENT_SOURCE_DIR}/ResolvServer.h
		${CMAKE_CURRENT_SOURCE_DIR}/ResolvSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/SctpSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/Semaphore.h
		${CMAKE_CURRENT_SOURCE_DIR}/SmtpdSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/Socket.h
		${CMAKE_CURRENT_SOURCE_DIR}/SocketAddress.h
		${CMAKE_CURRENT_SOURCE_DIR}/SocketHandler.h
		${CMAKE_CURRENT_SOURCE_DIR}/SocketHandlerEp.h
		${CMAKE_CURRENT_SOURCE_DIR}/SocketHandlerThread.h
		${CMAKE_CURRENT_SOURCE_DIR}/sockets-config.h
		${CMAKE_CURRENT_SOURCE_DIR}/SocketStream.h
		${CMAKE_CURRENT_SOURCE_DIR}/SocketThread.h
		${CMAKE_CURRENT_SOURCE_DIR}/socket_include.h
		${CMAKE_CURRENT_SOURCE_DIR}/SSLInitializer.h
		${CMAKE_CURRENT_SOURCE_DIR}/StdLog.h
		${CMAKE_CURRENT_SOURCE_DIR}/StdoutLog.h
		${CMAKE_CURRENT_SOURCE_DIR}/StreamSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/StreamWriter.h
		${CMAKE_CURRENT_SOURCE_DIR}/TcpSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/Thread.h
		${CMAKE_CURRENT_SOURCE_DIR}/UdpSocket.h
		${CMAKE_CURRENT_SOURCE_DIR}/Utility.h
		${CMAKE_CURRENT_SOURCE_DIR}/XmlDocument.h
		${CMAKE_CURRENT_SOURCE_DIR}/XmlException.h
		${CMAKE_CURRENT_SOURCE_DIR}/XmlNode.h
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Inc/${PROJECT_NAME}"
	)
	
	#file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}")
	#file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}")
	
	#INSTALL(DIRECTORY ${LIBRARY_OUTPUT_PATH} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}")
	
	#message(STATUS "fff" ${LIBRARY_OUTPUT_PATH})
	#message(STATUS "fff" ${CMAKE_CURRRENT_BINARY_DIR})
	#message(STATUS "fff" ${Sockets_BINARY_DIR})
	
	file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}")
	file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}")
	
	install(FILES 
		${Sockets_BINARY_DIR}/Debug/Sockets_d.lib
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}" CONFIGURATIONS Debug
	)
	install(FILES 
		${Sockets_BINARY_DIR}/Release/Sockets.lib
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}" CONFIGURATIONS Release None ""
	)
	install(FILES 
		${Sockets_BINARY_DIR}/RelWithDebInfo/Sockets.lib
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}" CONFIGURATIONS RelWithDebInfo
	)
	install(FILES 
		${Sockets_BINARY_DIR}/MinSizeRel/Sockets.lib
		DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/${PROJECT_NAME}" CONFIGURATIONS MinSizeRel
	)
	
endif(WIN32)
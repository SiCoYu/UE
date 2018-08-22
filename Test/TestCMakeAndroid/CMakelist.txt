#****************************This is Project Info****************************
PROJECT(TestCMakeAndroid)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
 
#****************************This is Compile Flag****************************
 if(DEBUG)        
 message( STATUS "==============================debug==============================" )        
 ADD_DEFINITIONS(-g)
 ADD_DEFINITIONS(-D AVX_DEBUG_LEVEL=AVX_DEBUG_DEBUG)
else(DEBUG)   
 message( STATUS "==============================release==============================" )         
 ADD_DEFINITIONS(-O2)
 ADD_DEFINITIONS(-D AVX_DEBUG_LEVEL=AVX_DEBUG_INFO)
 endif()
 
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__ANDROID__ -DANDROID")
 
#****************************This is Include File/Directories****************************
#INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(../../libextern/Android/include)
 
#****************************This is Source File/Directories****************************
SET(DIR_SRCS TestCMakeAndroid.cpp)
 
#****************************This is Library Directories****************************
LINK_DIRECTORIES(./)
LINK_DIRECTORIES(../../libextern/Android/lib)
 
#****************************This is 3Party Library****************************
#LINK_LIBRARIES(pthread)
 
#****************************This is Output Directory****************************
 
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../../bin/Android)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../../bin/Android)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/../../../bin/Android)
 
#****************************This is Output Library****************************
ADD_LIBRARY(TestCMakeAndroid SHARED ${DIR_SRCS} )
TARGET_LINK_LIBRARIES(TestCMakeAndroid)
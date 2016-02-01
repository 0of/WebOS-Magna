##################################################
#
#	This file is part of core library of Magna framework
#
#	Copyright (c) 2013 by Magnus( Magnusbackyard@gmail.com )
#
##################################################

#project name
PROJECT(basedef)

#cmake version shall not lower than 2.8
cmake_minimum_required(VERSION 2.8)

#compiler version check
IF(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
  IF(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7.2")
    MESSAGE(FATAL_ERROR "gcc version shall be higher than 4.7.2")
  ENDIF(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7.2")
ELSEIF(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
  IF(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "16.0.0")
    MESSAGE(FATAL_ERROR "MSVC version shall be higher than 16.0.0")
  ENDIF(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "16.0.0")
ELSE()
	MESSAGE(FATAL_ERROR "Unknown compiler")
ENDIF(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

FILE(GLOB SRC_LIST "./*.h" "./*.cpp" "./private/*.h" "./private/*.cpp")

IF(WIN32)
MESSAGE("Win32 build")
IF(CMAKE_COMPILER_IS_GNUCXX)
	FIND_LIBRARY(pthreadGCE2 ${LIBRARY_OUT_PATH} $ENV{PATH} )
	ADD_LIBRARY(pthreadGCE2 SHARED IMPORTED)
    #compiler as c++ 0x standard
    LIST( APPEND CMAKE_CXX_FLAGS "-std=c++0x" )
	
ELSE(CMAKE_COMPILER_IS_GNUCXX)
#find pthread-MSVC for windows
#0# not for all build
FIND_LIBRARY(pthreadVCE2 ${LIBRARY_OUT_PATH} $ENV{PATH})
ADD_LIBRARY(pthreadVCE2 SHARED IMPORTED)

ENDIF(CMAKE_COMPILER_IS_GNUCXX)
#add external dependencies
ADD_LIBRARY(kernel32 SHARED IMPORTED)
ADD_LIBRARY(user32 SHARED IMPORTED)
ADD_LIBRARY(winspool SHARED IMPORTED)
ADD_LIBRARY(comdlg32 SHARED IMPORTED)
ADD_LIBRARY(advapi32 SHARED IMPORTED)
ADD_LIBRARY(shell32 SHARED IMPORTED)

ELSE(WIN32)
    IF(CMAKE_COMPILER_IS_GNUCXX)
      #compiler as c++ 0x standard
      LIST( APPEND CMAKE_CXX_FLAGS "-lpthread -lrt -std=c++0x" )
    ENDIF(CMAKE_COMPILER_IS_GNUCXX)
ENDIF(WIN32)

#build shared lib
SET(BUILD_SHARED_LIBS ON)

#build as shared lib
ADD_LIBRARY(basedef SHARED ${SRC_LIST})


#post build script
#copy the built lib

IF(WIN32)
#do nothing

ELSE(WIN32)
#0# for all build

#linux///
SET( MAGNA_OUTPUT_LIB_PAPH ${basedef_SOURCE_DIR}/../lib/libbasedef.so )
SET( BASEDEF_BUILD_TARGET_PATH ${basedef_BINARY_DIR}/libbasedef.so )

ADD_CUSTOM_COMMAND( TARGET basedef POST_BUILD COMMAND rm -f ${MAGNA_OUTPUT_LIB_PAPH} )
ADD_CUSTOM_COMMAND( TARGET basedef POST_BUILD COMMAND cp -sf ${BASEDEF_BUILD_TARGET_PATH} ${MAGNA_OUTPUT_LIB_PAPH}  )
ENDIF(WIN32)


#copy header files
#SET( BASEDEF_BUILD_HEADER_FILES ${basedef_SOURCE_DIR}/*.h )
#ADD_CUSTOM_COMMAND( TARGET basedef POST_BUILD COMMAND cp -usf ${BASEDEF_BUILD_TARGET_PATH} ${MAGNA_OUTPUT_LIB_PAPH}  )

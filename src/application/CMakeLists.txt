PROJECT(application)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#output base directory
SET(MAGNA_DIR ${application_SOURCE_DIR}/..)

#src files
FILE(GLOB SRC_LIST "./*.h" "./*.cpp" "./private/*.h" "./private/*.cpp")

IF(WIN32)
MESSAGE("Win32")
ELSE(WIN32)
    IF(CMAKE_COMPILER_IS_GNUCXX)
      #compiler as c++ 0x standard
      list( APPEND CMAKE_CXX_FLAGS "-lpthread -lrt -std=c++0x" )
    ENDIF(CMAKE_COMPILER_IS_GNUCXX)
ENDIF(WIN32)

#build shared lib
SET(BUILD_SHARED_LIBS ON)

#build as shared lib
ADD_LIBRARY(${PROJECT_NAME} SHARED ${SRC_LIST})

#dependencies
INCLUDE_DIRECTORIES( ${MAGNA_DIR} )
#qt project is slightly different
INCLUDE_DIRECTORIES( ${MAGNA_DIR}/qt_glue_img )
INCLUDE_DIRECTORIES( ${MAGNA_DIR}/qt_glue )


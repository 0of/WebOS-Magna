PROJECT(basegui)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#output base directory
SET(MAGNA_DIR ${basegui_SOURCE_DIR}/..)

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

##BASEDEF
SET(MAGNA_BASEDEF_BUILD ${MAGNA_DIR}/basedef/basedef/ )

IF(NOT EXISTS ${MAGNA_BASEDEF_BUILD})
MESSAGE("basedef build dir not exists")
ENDIF(NOT EXISTS ${MAGNA_BASEDEF_BUILD})

LINK_DIRECTORIES(${MAGNA_BASEDEF_BUILD})

#links
ADD_LIBRARY(basedef SHARED IMPORTED)
###########################################

##INTERPRET
SET(MAGNA_INTERPRET_BUILD ${MAGNA_DIR}/interpret/interpret)

IF(NOT EXISTS ${MAGNA_INTERPRET_BUILD})
MESSAGE("qt interpert dir not exists")
ENDIF(NOT EXISTS ${MAGNA_INTERPRET_BUILD})

LINK_DIRECTORIES(${MAGNA_INTERPRET_BUILD})

#links
ADD_LIBRARY(interpret SHARED IMPORTED)
###########################################

##QT_GLUE_IMG
SET(MAGNA_QT_GLUE_IMG_BUILD ${MAGNA_DIR}/qt_glue_img/Build)

IF(NOT EXISTS ${MAGNA_QT_GLUE_IMG_BUILD})
MESSAGE("qt glue img build dir not exists")
ENDIF(NOT EXISTS ${MAGNA_QT_GLUE_IMG_BUILD})

LINK_DIRECTORIES(${MAGNA_QT_GLUE_IMG_BUILD})

#links
ADD_LIBRARY(qt_glue_img SHARED IMPORTED)
###########################################

##QT_GLUE
SET(MAGNA_QT_GLUE_BUILD ${MAGNA_DIR}/qt_glue/Build)

IF(NOT EXISTS ${MAGNA_QT_GLUE_BUILD})
MESSAGE("qt glue build dir not exists")
ENDIF(NOT EXISTS ${MAGNA_QT_GLUE_BUILD})

LINK_DIRECTORIES(${MAGNA_QT_GLUE_BUILD})

#links
ADD_LIBRARY(qt_glue SHARED IMPORTED)
###########################################

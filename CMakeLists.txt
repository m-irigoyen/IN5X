cmake_minimum_required(VERSION 2.8) 
PROJECT (IN5X)
find_package(OpenCV REQUIRED )

SET(EXE_NAME "IN5X")

FILE (GLOB_RECURSE sourceFiles src/*)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )

FILE(GLOB_RECURSE SRCS_RECON
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Reconnaissance/*.cpp 
	${IA54_SOURCE_DIR}/src/Reconnaissance/*.h)
	FILE(GLOB_RECURSE SRCS_RECONPREP
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/ReconnaissancePreparation/*.cpp 
	${IA54_SOURCE_DIR}/src/ReconnaissancePreparation/*.h)
	FILE(GLOB_RECURSE SRCS_UTILITIES
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/Utilities/*.cpp 
	${IA54_SOURCE_DIR}/src/Utilities/*.h)
	FILE(GLOB_RECURSE SRCS_MAIN
	${IA54_SOURCE_DIR}
	${IA54_SOURCE_DIR}/src/main.cpp 
	${IA54_SOURCE_DIR}/src/exampleCode.h)
	
	
source_group(Reconnaissance FILES ${SRCS_RECON})
source_group(ReconnaissancePreparation FILES ${SRCS_RECONPREP})
source_group(Utilities FILES ${SRCS_UTILITIES})

link_directories( ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_EXE_LINKER_FLAGS "-static")

ADD_EXECUTABLE(${EXE_NAME} ${SRCS_RECON} ${SRCS_RECONPREP} ${SRCS_UTILITIES} ${SRCS_MAIN})

target_link_libraries( IN5X ${OpenCV_LIBS} )

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()
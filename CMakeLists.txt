cmake_minimum_required(VERSION 2.8) 
PROJECT (IN5X)
find_package(OpenCV REQUIRED )

SET(EXE_NAME "IN5X")

FILE (GLOB_RECURSE sourceFiles src/*)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )

FILE(GLOB_RECURSE SRCS_RECON
	${IN5X_SOURCE_DIR}
	${IN5X_SOURCE_DIR}/src/Reconaissance/*.cpp 
	${IN5X_SOURCE_DIR}/src/Reconaissance/*.h)
	FILE(GLOB_RECURSE SRCS_RECONPREP
	${IN5X_SOURCE_DIR}
	${IN5X_SOURCE_DIR}/src/ReconaissancePreparation/*.cpp 
	${IN5X_SOURCE_DIR}/src/ReconaissancePreparation/*.h)
	FILE(GLOB_RECURSE SRCS_UTILITIES
	${IN5X_SOURCE_DIR}
	${IN5X_SOURCE_DIR}/src/Utilities/*.cpp 
	${IN5X_SOURCE_DIR}/src/Utilities/*.h)
	FILE(GLOB_RECURSE SRCS_MAIN 
	${IN5X_SOURCE_DIR}/src 
	main.cpp)
	
	
source_group(Reconaissance FILES ${SRCS_RECON})
source_group(ReconaissancePreparation FILES ${SRCS_RECONPREP})
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
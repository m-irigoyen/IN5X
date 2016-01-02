cmake_minimum_required(VERSION 2.8) 
 PROJECT (IN5X)
 find_package(OpenCV REQUIRED )
 
 FILE (GLOB_RECURSE sourceFiles src/*)
 
 INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
  link_directories( ${CMAKE_BINARY_DIR}/bin)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
  
  SET(CMAKE_EXE_LINKER_FLAGS "-static")
  
  add_executable( IN5X ${sourceFiles} )
  
 target_link_libraries( IN5X ${OpenCV_LIBS} )
 
 if (MSVC)
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
     set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
 endif()
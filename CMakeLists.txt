cmake_minimum_required(VERSION 2.8.7)
project(binary_log)


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH   ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(Eigen3 REQUIRED)


if(CMAKE_SYSTEM_PROCESSOR MATCHES "^x86_64" )
	message(STATUS "Architecture is x84_64, compiling with SSE")
	# SSE flags
	add_definitions("-DENABLE_SSE")

	# Also add some useful compiler flag
	set(CMAKE_CXX_FLAGS
	   "${CMAKE_CXX_FLAGS} -O2 ${SSE_FLAGS} -march=native  -std=c++0x"
	)
endif()
if(CMAKE_SYSTEM_PROCESSOR MATCHES "^arm")
	message(STATUS "Architecture is arm, compiling with NEON")
	# NEON flags
	add_definitions("-DENABLE_NEON")

	# Also add some useful compiler flag
	set(CMAKE_CXX_FLAGS
	   "${CMAKE_CXX_FLAGS} -O2 -march=native -mfpu=neon -std=c++0x"
	)  
endif()

# Set source files
set(log_SOURCE_FILES
  ${PROJECT_SOURCE_DIR}/src/BinaryLog.cpp
)
set(SOURCE_FILES
  ${log_SOURCE_FILES}
)

include_directories(
  ${EIGEN3_INCLUDE_DIR}
  ${PROJECT_SOURCE_DIR}/src
)


# build shared library.
add_library(binaryLog_lib SHARED ${SOURCE_FILES})

target_link_libraries(binaryLog_lib ${Boost_LIBRARIES})


# build test program
add_executable(log_test src/test/main_test.cpp)
add_executable(unpack src/test/unpack.cpp)
target_link_libraries(log_test binaryLog_lib)
target_link_libraries(unpack binaryLog_lib)

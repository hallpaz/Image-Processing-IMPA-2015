cmake_minimum_required(VERSION 3.2)
project("Camera Calibration")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package( OpenCV REQUIRED )
include_directories(include ${OpenCV_INCLUDE_DIRS} )

file( GLOB SOURCES "src/*.cpp")

file(MAKE_DIRECTORY "build/images")
file(MAKE_DIRECTORY "build/reprojected")
file(MAKE_DIRECTORY "build/parameters")

add_executable( calib ${SOURCES} )
target_link_libraries( calib ${OpenCV_LIBS} )

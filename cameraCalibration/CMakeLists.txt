cmake_minimum_required(VERSION 3.2)
project("Camera Calibration")
find_package( OpenCV REQUIRED )
include_directories(include ${OpenCV_INCLUDE_DIRS} )

file( GLOB SOURCES "src/*.cpp")

file(MAKE_DIRECTORY "build/captured")
file(MAKE_DIRECTORY "build/reprojected")
file(MAKE_DIRECTORY "build/parameters")

set_property(TARGET tgt PROPERTY CXX_STANDARD 11)

add_executable( calib ${SOURCES} )
target_link_libraries( calib ${OpenCV_LIBS} )

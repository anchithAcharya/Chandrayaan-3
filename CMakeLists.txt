cmake_minimum_required(VERSION 3.19)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

project(CG_Project___Lunar_Lander)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(CG_Project___Lunar_Lander includes/stb_image.h main.cpp includes/main.h common.cpp includes/common.h Camera.cpp includes/Camera.h Player.cpp includes/Player.h Drawable.cpp includes/Drawable.h rover.cpp includes/rover.h)

include_directories(includes)

find_library(FREEGLUT_LIB freeglut lib)
target_link_libraries(CG_Project___Lunar_Lander LINK_PUBLIC opengl32 glu32 ${FREEGLUT_LIB})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_library(common STATIC common.cpp)
add_library(Camera STATIC Camera.cpp)
add_library(Drawable STATIC Drawable.cpp)
add_library(Player STATIC Player.cpp)
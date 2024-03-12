cmake_minimum_required(VERSION 3.12)

# Define a "project", providing a description and a programming language
project(aMAZEd,
	VERSION 1.0
	DESCRIPTION "An easy maze generating and solving program"
	LANGUAGES CXX
)

find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package( Threads )

# Our "project" will be able to build an executable out of a C++ source file
add_executable(exe
   	 src/main.cpp
)

# Our project will be able to build a library
add_library(Lib
	src/maze.cpp
	src/draw.cpp
	src/mazeGen.cpp)

# This is needed if we keep .h files in the "include" directory
target_include_directories(Lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(
	Lib PUBLIC
	glfw)

target_link_libraries(
	Lib PUBLIC 
	OpenGL::GL)

target_link_libraries( 
	exe PUBLIC 
	${CMAKE_THREAD_LIBS_INIT} )

# Target commands tells which dependencies targer exec have
target_link_libraries(
    exe PUBLIC 
    Lib
)

# Force the compiler to use the C++17 standard
target_compile_features(exe PUBLIC cxx_std_17)


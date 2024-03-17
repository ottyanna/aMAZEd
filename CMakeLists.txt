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

# boost setup
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost REQUIRED) 

# Our "project" will be able to build an executable out of a C++ source file
add_executable(exe
   	 src/main.cpp
)

# Our project will be able to build a library
add_library(Lib
	src/maze.cpp
	src/draw.cpp
	src/mazeGen.cpp
	src/mazeSolve.cpp
	src/vertex.cpp)

# This is needed if we keep .h files in the "include" directory
target_include_directories(Lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)


if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    # add_executable(exe file1.cxx file2.cxx) 
    target_link_libraries(Lib PUBLIC Boost::boost)
endif()

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


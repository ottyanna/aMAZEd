cmake_minimum_required(VERSION 3.12)

# Define a "project", providing a description and a programming language
project(aMAZEd,
	VERSION 1.0
	DESCRIPTION "An easy maze generating and solving program"
	LANGUAGES CXX
)

# Our "project" will be able to build an executable out of a C++ source file
add_executable(exe
   	 src/main.cpp
)

# Force the compiler to use the C++17 standard
target_compile_features(exe PUBLIC cxx_std_17)


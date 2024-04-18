cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

set(PROJECT_NAME JeanDujardin)

project(${PROJECT_NAME} VERSION 0.0.1 LANGUAGES CXX C)

# Add property to allow making project folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON CACHE BOOL "")
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON CACHE BOOL "")
set(CMAKE_POSITION_INDEPENDENT_CODE ON CACHE BOOL "Whether to create a position-independent target")

# Multithreaded MSVC builds
if(MSVC_VERSION GREATER 1500 AND ${CMAKE_VERSION} VERSION_GREATER "2.8.6")
	include(ProcessorCount)
	ProcessorCount(N)
	if(NOT N EQUAL 0)
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP${N}" CACHE STRING "" FORCE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /MP${N}" CACHE STRING "" FORCE)
		set(CMAKE_CSharp_FLAGS "${CMAKE_CSharp_FLAGS} /m:${N}" CACHE STRING "" FORCE)
	endif()
endif()

# Force all compilers to use the correct C and C++ standard versions.
# Needed to allow for CheckCXXSourceCompiles to work correctly.
set(CMAKE_REQUIRED_FLAGS "-std=c++20 -std=c11")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

link_directories(${CMAKE_SOURCE_DIR}/extern/glew-2.1.0/lib/Release/x64)

# App sources directory
add_subdirectory(Sources)

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
cmake_minimum_required(VERSION 3.5)

# cmake -DCMAKE_BUILD_TYPE=Debug or Release

# project name
project(BonDriver_DVBC)

message(STATUS "System Information")
message(STATUS "System = ${CMAKE_SYSTEM_NAME}")
message(STATUS "Compiler = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "UNIX = ${UNIX}")
message(STATUS "APPLE = ${APPLE}")

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE INTERNAL "limit build types" FORCE)
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "default build type")

add_subdirectory(src)

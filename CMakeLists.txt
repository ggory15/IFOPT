# Copyright (c) 2017, Alexander W. Winkler, ETH Zurich. All rights reserved.
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

SET(CXX_DISABLE_WERROR TRUE)
INCLUDE(cmake/base.cmake)
INCLUDE(cmake/boost.cmake)
INCLUDE(cmake/eigen.cmake)
INCLUDE(cmake/test.cmake)

SET(PROJECT_NAME "ifopt")
SET(PROJECT_DESCRIPTION "This is repacking the iforpt, Nonlinear Programming Solver")
SET(PROJECT_URL "https://github.com/ethz-adrl/ifopt")

set(BUILD_DOCUMENTATION OFF)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -Wall -Wwrite-strings -pedantic -O3 -funroll-loops -fPIC")


SETUP_PROJECT()
SEARCH_FOR_BOOST()

ADD_REQUIRED_DEPENDENCY("eigen3 >= 3.0")
include_directories(${EIGEN3_INCLUDE_DIRS})


# set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake2" ${CMAKE_MODULE_PATH})
# find_package(IPOPT 3.11.9 REQUIRED)
set(IPOPT_INCLUDE_DIRS /usr/include/coin)
include_directories(${IPOPT_INCLUDE_DIRS})
add_definitions(-DHAVE_STDDEF_H)

#set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/ifopt_core/include")
SET(${PROJECT_NAME}_HEADERS
	include/ifopt_core/bounds.h
	include/ifopt_core/composite.h
	include/ifopt_core/constraint_set.h
	include/ifopt_core/cost_term.h
	include/ifopt_core/problem.h
	include/ifopt_core/solver.h
	include/ifopt_core/variable_set.h
#
	include/ifopt_ipopt/ipopt_adapter.h
	include/ifopt_ipopt/ipopt_solver.h
#
	
)
#include_directories(${PROJECT_NAME}_HEADERS)

add_subdirectory (src)
add_subdirectory (test)
add_subdirectory (demo)
PKG_CONFIG_APPEND_LIBS("ifopt")

#INSTALL(TARGETS ${LIB_CORE} DESTINATION lib)

SETUP_PROJECT_FINALIZE()

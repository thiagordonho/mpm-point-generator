project(mpm-point-gen LANGUAGES CXX)

# Require C++14-compliant compiler; only available for CMake v. 3.1 and up
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_minimum_required(VERSION 3.1)

SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

# General compile settings
IF (NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "RelWithDebInfo")
ENDIF (NOT CMAKE_BUILD_TYPE)

# GNU Specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter -Wno-missing-braces -Wno-misleading-indentation -Wno-deprecated-declarations")
endif()

# OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#  add_compile_options(${OpenMP_CXX_FLAGS})
endif()

# CMake Modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Eigen
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# Boost FileSystem
find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${BOOST_INCLUDE_DIRS})
link_libraries(${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

# Include directories
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/external
)

# mpm_point_generator executable
SET(mpm_point_gen_src
  src/element.cc
  src/main.cc
  src/io.cc
  src/material_properties.cc
)
add_executable(mpm_point_generator ${mpm_point_gen_src})

# Unit test
SET(test_src
  ${PROJECT_SOURCE_DIR}/src/material_properties.cc
  ${PROJECT_SOURCE_DIR}/src/element.cc
  ${PROJECT_SOURCE_DIR}/tests/test_main.cc  
  ${PROJECT_SOURCE_DIR}/tests/point_test.cc
  ${PROJECT_SOURCE_DIR}/tests/material_properties_test.cc
  ${PROJECT_SOURCE_DIR}/tests/volume_test.cc
  ${PROJECT_SOURCE_DIR}/tests/gmsh_test_2d.cc
  ${PROJECT_SOURCE_DIR}/tests/gmsh_test_3d.cc
)
add_executable(mpm_point_generator_unit_test ${test_src})
add_test(NAME mpm_point_generator_unit_test COMMAND $<TARGET_FILE:mpm_point_generator_unit_test>)
enable_testing()

# Coverage
find_package(codecov)
if(ENABLE_COVERAGE)
  add_coverage(mpm_point_generator_unit_test)
endif()

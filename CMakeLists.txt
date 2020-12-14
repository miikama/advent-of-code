cmake_minimum_required(VERSION 3.4)
project(advent-of-code LANGUAGES CXX)

# global project compile flags
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -Wall -Werror -std=c++17 -lstdc++ -lm -fPIC")

# add the cpp part of the code
add_subdirectory(src/advent_processing ${ADVENT_OUTPUT_BINARIES_DIR})


#######################################################
#                PYBIND
#######################################################
#
#   See https://pybind11.readthedocs.io/en/stable/compiling.html
#
add_subdirectory(pybind11)

# We have our bindings in a single file
set(BINDINGS src/advent_processing/bindings.cpp)

# If you have a single cpp file, you'd do the following
#
#   pybind11_add_module(advent_processing src/advent_processing/bindings.cpp advent_processing_lib)
#
# And then link the target with our code
#
#   add_library(advent_processing_lib ${BINDINGS} ${ADVENT_OF_CODE_SOURCES})
#   target_include_directories(advent_processing_lib INTERFACE src/advent_processing)
#   target_link_libraries(advent_processing PRIVATE advent_processing_lib)
# 
# but it does not work since pybind11_add_module(advent_processing)
# already uses the target_link_libraries command internally.
#
# Instead, we do the functionality of 'pybind11_add_module' manually
#
add_library(advent_processing MODULE ${BINDINGS} ${ADVENT_OF_CODE_SOURCES})
target_link_libraries(advent_processing PRIVATE pybind11::module pybind11::lto pybind11::windows_extras)
target_include_directories(advent_processing INTERFACE src/advent_processing)
pybind11_extension(advent_processing)
pybind11_strip(advent_processing)

# from pybind11 docs
set_target_properties(advent_processing PROPERTIES CXX_VISIBILITY_PRESET "hidden"
                                         CUDA_VISIBILITY_PRESET "hidden")
# Link the created bindings against our other sources
# target_link_libraries(advent_processing STATIC advent_processing_lib)

#######################################################
#                PYBIND
#######################################################


## This is how you get the python headers if you need them
# find_package(Python COMPONENTS Interpreter Development)
# set(ADVENT_OF_CODE_EXT_INCLUDE_DIRS ${pybind11_INCLUDE_DIR} ${Python_INCLUDE_DIRS})
# message(STATUS "Pybind11 include dirs ${ADVENT_OF_CODE_EXT_INCLUDE_DIRS}")

# output binary directory
# set(ADVENT_OUTPUT_BINARIES_DIR bin)

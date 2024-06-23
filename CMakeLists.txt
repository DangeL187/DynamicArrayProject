cmake_minimum_required(VERSION 3.22)
project(DynamicArrayProject)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(pybind11)

include_directories(include)

file(GLOB_RECURSE HEADER_FILES "include/*.hpp" "include/*.tpp")
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

pybind11_add_module(DynamicArrayProject ${HEADER_FILES} ${SOURCE_FILES})

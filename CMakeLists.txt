cmake_minimum_required(VERSION 3.5)

project(ProjectName CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(test)
add_subdirectory(lib/googletest)
add_subdirectory(app)

cmake_minimum_required(VERSION 3.5)
set(LIB_NAME ${CMAKE_PROJECT_NAME}_lib)

if(NOT IS_DIRECTORY "${PROJECT_SOURCE_DIR}/lib/googletest")
	execute_process(COMMAND git clone https://github.com/google/googletest.git WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
endif()

set(INCLUDE_DIR "./include")
set(SRC_DIR "./src")

file(GLOB SOURCES
    "${SRC_DIR}/*.cpp"
)


add_library(LIB_NAME STATIC ${SOURCES})
set_target_properties(LIB_NAME PROPERTIES LINKER_LANGUAGE CXX)


target_include_directories(LIB_NAME PUBLIC  ${INCLUDE_DIR})
target_include_directories(LIB_NAME PUBLIC ${SRC_DIR})


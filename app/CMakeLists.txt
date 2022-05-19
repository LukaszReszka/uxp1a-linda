cmake_minimum_required(VERSION 3.5)

set(INCLUDE_DIR "./include")
set(SRC_DIR "./src")

file(GLOB SOURCES
        "${SRC_DIR}/*.cpp"
)

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
    set_property(TARGET my_app PROPERTY COMPILE_OPTIONS "-pthread")
    set_property(TARGET my_app PROPERTY INTERFACE_COMPILE_OPTIONS "-pthread")
endif()

add_library(LIB_INTERPRETER STATIC ${SOURCES})
set_target_properties(LIB_INTERPRETER PROPERTIES LINKER_LANGUAGE CXX)
if(CMAKE_THREAD_LIBS_INIT)
    target_link_libraries(LIB_INTERPRETER "${CMAKE_THREAD_LIBS_INIT}")
endif()

target_include_directories(LIB_INTERPRETER PUBLIC  ${INCLUDE_DIR})
target_include_directories(LIB_INTERPRETER PUBLIC ${SRC_DIR})
target_link_libraries(LIB_INTERPRETER PUBLIC LIB_NAME)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC LIB_INTERPRETER)

install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build)
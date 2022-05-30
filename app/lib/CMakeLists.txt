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



add_library(LIB_APP STATIC ${SOURCES})
set_target_properties(LIB_APP PROPERTIES LINKER_LANGUAGE CXX)
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(LIB_APP PUBLIC "${CMAKE_THREAD_LIBS_INIT}")
endif()

target_link_libraries(LIB_APP PUBLIC LIB_NAME)
target_include_directories(LIB_APP PUBLIC  ${INCLUDE_DIR})
target_include_directories(LIB_APP PUBLIC ${SRC_DIR})

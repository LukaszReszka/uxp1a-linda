add_subdirectory(lib)

add_executable(${CMAKE_PROJECT_NAME} main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC LIB_NAME)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC LIB_APP)

install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/build)

set(BINARY ${CMAKE_PROJECT_NAME}_tst)
file(GLOB TEST_SOURCES *.cpp)


add_executable(${BINARY} ${TEST_SOURCES})

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC LIB_NAME gtest)
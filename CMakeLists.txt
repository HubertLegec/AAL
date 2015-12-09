cmake_minimum_required(VERSION 3.3)
project(RING)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Download and unpack gtest at configure time
configure_file(gtest-CMakeLists.txt gtest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gtest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gtest-download )

# Add gtest directly to our build
add_subdirectory(${CMAKE_BINARY_DIR}/gtest-src
        ${CMAKE_BINARY_DIR}/gtest-build
        EXCLUDE_FROM_ALL )

# Add the gtest include directory, since gtest
# doesn't add that dependency to its gtest target
target_include_directories(gtest INTERFACE
        "${CMAKE_BINARY_DIR}/gtest-src/include" )


set(AAL_SOURCE_FILES AAL/sources/main.cpp )
add_executable(AAL ${AAL_SOURCE_FILES})


# Tests configuration
add_executable(AAL_TESTS )
target_link_libraries(AAL_TESTS gtest_main)
add_test(NAME aalTest COMMAND aalTest)

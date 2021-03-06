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


set(AAL_SOURCE_FILES AAL/main.cpp
        AAL/sources/Line2D.cpp
        AAL/sources/Point2D.cpp
        AAL/sources/Polygon.cpp
        AAL/sources/Prism.cpp
        AAL/sources/PrismGenerator.cpp
        AAL/sources/UserInterface.cpp
        AAL/sources/Vector2D.cpp
        AAL/sources/WeilerAtherton.cpp
        AAL/sources/SweepMethod.cpp
        AAL/sources/EdgeEndpoint.cpp AAL/sources/Executor.cpp
        AAL/sources/TempBuffer.cpp
        AAL/headers/Timer.h)
add_executable(AAL ${AAL_SOURCE_FILES})


# Tests configuration
set(AAL_TEST_FILES AAL/sources/Line2D.cpp
        AAL/sources/Point2D.cpp
        AAL/sources/Polygon.cpp
        AAL/sources/Prism.cpp
        AAL/sources/Vector2D.cpp
        AAL/sources/EdgeEndpoint.cpp
        AAL/sources/TempBuffer.cpp)
add_executable(AAL_TESTS AAL_TESTS/weilerAthertonTest.cpp
        AAL/sources/WeilerAtherton.cpp
        ${AAL_TEST_FILES})
target_link_libraries(AAL_TESTS gtest_main)
add_test(NAME aalTest COMMAND aalTest)


add_executable(AAL_GENERATOR_TEST AAL_TESTS/generatorTest.cpp
        AAL/sources/Point2D.cpp
        AAL/sources/Polygon.cpp
        AAL/sources/Line2D.cpp
        AAL/sources/Prism.cpp
        AAL/sources/Vector2D.cpp
        AAL/sources/WeilerAtherton.cpp
        AAL/sources/EdgeEndpoint.cpp
        AAL/sources/PrismGenerator.cpp)

target_link_libraries(AAL_GENERATOR_TEST gtest_main)
add_test(NAME generatorTest COMMAND generatorTest)

add_executable(AAL_SWEEP_TEST AAL_TESTS/sweepTest.cpp
        AAL/sources/SweepMethod.cpp
        ${AAL_TEST_FILES})
target_link_libraries(AAL_SWEEP_TEST gtest_main)
add_test(NAME sweepTest COMMAND sweepTest)

add_executable(AAL_EXECUTOR_TEST AAL_TESTS/executorTest.cpp
        AAL/sources/PrismGenerator.cpp
        AAL/sources/Executor.cpp
        AAL/sources/WeilerAtherton.cpp
        AAL/sources/SweepMethod.cpp
        ${AAL_TEST_FILES})
target_link_libraries(AAL_EXECUTOR_TEST gtest_main)
add_test(NAME executorTest COMMAND executorTest)
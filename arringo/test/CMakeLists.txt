cmake_minimum_required(VERSION 3.13)
project(league_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


set(SOURCES main_test.cpp test.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
        gtest
        tournament_simulation
        )

# enable testing
enable_testing()

# define tests
add_test(
        NAME ${PROJECT_NAME}
        COMMAND ${PROJECT_NAME}
)
cmake_minimum_required (VERSION 3.13)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++17")

project (tournament_simulation)
set(SOURCES main.cpp Team.hpp LeagueSimulator.hpp)

 
add_library(tournament_simulation STATIC ${SOURCES})
add_executable(tournament_simulation_run ${SOURCES})
cmake_minimum_required(VERSION 2.8.7)
project(wmc_sim)

SET(CMAKE_CXX_FLAGS "-std=c++11")
SET(CMAKE_BUILD_TYPE RELEASE)

find_package(Boost REQUIRED)

include_directories(include ${Boost_INCLUDE_DIR})

add_executable(wmc_sim src/wmc_sim.cpp src/tournament.cpp src/team.cpp src/pairing.cpp src/standing.cpp src/elo.cpp)

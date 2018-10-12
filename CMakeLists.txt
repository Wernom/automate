# How to use:
#   mkdir build
#   cd build
#   cmake ..
#   make
#
cmake_minimum_required(VERSION 3.0)

project(FA CXX C)

find_package(Threads)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -O2 -g")

add_executable(testfa
  testfa.cc
  Automaton.cc
  googletest/googletest/src/gtest-all.cc
)

target_include_directories(testfa
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest"
)

target_link_libraries(testfa
  PRIVATE
    ${CMAKE_THREAD_LIBS_INIT}
)

add_executable(fa
  fa.cc
  Automaton.cc
)

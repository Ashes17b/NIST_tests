cmake_minimum_required(VERSION 3.14)
  
project(testsSequence)

set(SRC_PATH src/Boltach)

set(CMAKE_CXX_STANDARD 17)

set(${PROJECT_NAME}_SRC
   ${SRC_PATH}/main.cpp
   ${SRC_PATH}/runs_test_boltach.cpp
)

find_package(Boost 1.68.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

#########################################################
# Executable
add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_SRC} )
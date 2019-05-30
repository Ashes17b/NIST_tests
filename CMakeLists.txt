cmake_minimum_required(VERSION 3.14)
  
project(testsSequence)

set(SRC_PATH src)

set(CMAKE_CXX_STANDARD 17)

set(${PROJECT_NAME}_SRC
   ${SRC_PATH}/main.cpp
   ${SRC_PATH}/utils/cephes.cpp
   ${SRC_PATH}/Boltach/runs_test_boltach.cpp
   ${SRC_PATH}/Boltach/random_excursion_variant_test_boltach.cpp
   ${SRC_PATH}/Timoshenko/runs_test_timoshenko.cpp
   ${SRC_PATH}/Timoshenko/random_excursions_test_timoshenko.cpp
   ${SRC_PATH}/Bondarev/random_excursions_test_bondarev.cpp
   ${SRC_PATH}/Bondarev/longest_runs_test_bondarev.cpp
   ${SRC_PATH}/Vecherko/non_overlapping_template_matching_test_vecherko.cpp
   ${SRC_PATH}/Lisai/serial_test_lisai.cpp
   ${SRC_PATH}/Lisai/spectral_test_lisai.cpp
   ${SRC_PATH}/Zakrevsky/serial_test_zakrevsky.cpp
   ${SRC_PATH}/Grudinsky/approximate_entropy_test_grudinsky.cpp
   ${SRC_PATH}/Vecherko/binary_matrix_rank_test_vecherko.cpp
   ${SRC_PATH}/Vecherko/spectral_test_vecherko.cpp
   ${SRC_PATH}/Grudinsky/spectral_test_grudinsky.cpp
   ${SRC_PATH}/Vecherko/linear_complexity_test_vecherko.cpp
)

find_package(Boost 1.65.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

#########################################################
# Executable
add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_SRC} )
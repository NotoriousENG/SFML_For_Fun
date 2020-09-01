# CMakeList.txt : CMake project for SFML_For_Fun, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

add_executable (SFML_For_Fun "SFML_For_Fun.cpp" "SFML_For_Fun.h")

target_link_libraries(SFML_For_Fun PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# TODO: Add tests and install targets if needed.

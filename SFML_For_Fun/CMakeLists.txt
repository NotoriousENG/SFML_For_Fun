# CMakeList.txt : CMake project for SFML_For_Fun, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
find_package(SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

add_executable (TinyBazooka "main.cpp" "main.h" "Hero.h" "Hero.cpp" "Enemy.h" "Enemy.cpp" "Rocket.h" "Rocket.cpp")

target_link_libraries(TinyBazooka PUBLIC sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# TODO: Add tests and install targets if needed.

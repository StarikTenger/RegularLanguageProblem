# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 17)

# Set the project name
project (little_onion)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/main.cpp
	src/objects/Parcer.cpp
	src/objects/Terminal.cpp
	src/objects/Nonterminal.cpp
	src/objects/Production.cpp
	src/objects/Grammar.cpp
    src/objects/LinearCFGChecker.cpp
)

# Add an executable with the above sources
add_executable(little_onion ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(little_onion
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/objects
)

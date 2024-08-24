cmake_minimum_required(VERSION 3.28)
project(ConsoleApplication3)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the SFML directory and include directories
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
include_directories("C:/SFML/include")

# Find the SFML components (ensure SFML_DIR is correctly set)
find_package(SFML COMPONENTS system window graphics audio REQUIRED)

# Add the executable target
add_executable(ConsoleApplication3 main.cpp frog.cpp drawmap.cpp global.cpp car.cpp carmanager.cpp
        drawtext.cpp
        Log.cpp
        header/log.h
        header/rivermanager.h
        rivermanager.cpp
        header/turtle.h
        turtle.cpp
        header/ultil.h
        boss.cpp
        bullet.cpp
        header/gamestate.h
        header/gamestate.h
        witch.cpp
        coin.cpp
        header/Bolt.h
        header/Lightning.h
        Lightning.cpp
        header/Letter.h
        Letter.cpp
        test.cpp
)

# Specify the library directory (this should be unnecessary if SFML_DIR is set correctly)
link_directories("C:/mingw64/lib")

# Link the SFML libraries and the legacy_stdio_definitions library
target_link_libraries(ConsoleApplication3 sfml-system sfml-window sfml-graphics sfml-audio)

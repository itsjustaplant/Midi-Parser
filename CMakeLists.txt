cmake_minimum_required(VERSION 3.17)
project(Midi_Parser)

#https://cmake.org/cmake/help/v3.12/command/string.html
string(TIMESTAMP DATE "%Y%m%d%H%M")

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(./tests/valgrind)
add_subdirectory(./tests/googletest)
add_subdirectory(./lib/googletest)


add_executable(midi_parser src/main.cpp src/midi_file.cpp include/midi_file.h include/track.h src/track.cpp)

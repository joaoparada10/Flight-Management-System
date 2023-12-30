cmake_minimum_required(VERSION 3.10)
project(AEDProject2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

add_executable(main src/main.cpp src/FileReader.cpp src/Airline.cpp src/Airport.cpp src/FMSGraph.cpp src/Menu.cpp src/Flight.cpp)

cmake_minimum_required(VERSION 3.11)
project(InitialSetSolver)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(InitialSetSolver src/Main.cpp src/Parse.cpp src/AF.cpp 
src/SCC.cpp src/CharacteristicFunction.cpp src/ContainsADM.cpp src/IsInitial.cpp
src/Encodings.cpp src/CadicalSatSolver.cpp src/EE-PROC.cpp src/EE-IT.cpp)


find_library(
    CADICAL
    NAMES libcadical.a
    PATHS lib/cadical-rel-2.1.3/build
    REQUIRED
)

find_path(
    CADICAL_INC_DIR
    NAMES cadical.hpp
    PATHS lib/cadical-rel-2.1.3/src
    REQUIRED
)

target_link_libraries(InitialSetSolver ${CADICAL})
target_include_directories(InitialSetSolver PUBLIC ${CADICAL_INC_DIR} )
target_include_directories(InitialSetSolver PUBLIC include)
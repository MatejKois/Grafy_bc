cmake_minimum_required(VERSION 3.18)
project(Grafy)

set(CMAKE_CXX_STANDARD 14)

set(
        SOURCES
        "${CMAKE_SOURCE_DIR}/Sources/main.cpp"
        "${CMAKE_SOURCE_DIR}/Sources/Algorithms/Dijkstra.cpp"
        "${CMAKE_SOURCE_DIR}/Sources/Algorithms/DijkstraBidirectional.cpp"
        "${CMAKE_SOURCE_DIR}/Sources/Algorithms/DijkstraPthread.cpp"
        "${CMAKE_SOURCE_DIR}/Sources/Algorithms/Dijstra_MPI.cpp"
        "${CMAKE_SOURCE_DIR}/Sources/Algorithms/Floyd.cpp"
        "${CMAKE_SOURCE_DIR}/Sources/Algorithms/FloydPthread.cpp"
        "${CMAKE_SOURCE_DIR}/Sources/Generator/GraphGenerator.cpp"
        "${CMAKE_SOURCE_DIR}/Sources/Generator/GraphMerger.cpp"
        "${CMAKE_SOURCE_DIR}/Sources/Matrix/DistanceMatrix.cpp"
        "${CMAKE_SOURCE_DIR}/Sources/Parser/Parser.cpp"
)

add_executable(Grafy ${SOURCES})

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

target_link_libraries(Grafy ${MPI_CXX_LIBRARIES})

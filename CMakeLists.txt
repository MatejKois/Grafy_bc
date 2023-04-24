cmake_minimum_required(VERSION 3.16)
project(Grafy)

set(CMAKE_CXX_STANDARD 14)

set(
        SOURCES

        "Sources/main.cpp"
        "Sources/Algorithms/Floyd.cpp"
        "Sources/Algorithms/Floyd_MPI.cpp"
        "Sources/Algorithms/FloydPthread.cpp"
        "Sources/Algorithms/LabelCorrect.cpp"
        "Sources/Algorithms/LabelCorrect_MPI.cpp"
        "Sources/Algorithms/LabelCorrectPthread.cpp"
        "Sources/Algorithms/LabelSet.cpp"
        "Sources/Algorithms/LabelSet_MPI.cpp"
        "Sources/Algorithms/LabelSetPthread.cpp"
        "Sources/Generator/GraphGenerator.cpp"
        "Sources/Generator/GraphMerger.cpp"
        "Sources/GraphStructures/DistanceMatrix.cpp"
        "Sources/GraphStructures/EdgesList.cpp"
        "Sources/Parser/Parser.cpp"
)

add_executable(Grafy ${SOURCES})

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

target_link_libraries(Grafy ${MPI_CXX_LIBRARIES} pthread)

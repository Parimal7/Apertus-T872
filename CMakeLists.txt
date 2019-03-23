cmake_minimum_required(VERSION 3.10)
project (RAWtoPPM)

include_directories(include) 

add_library(
    Debayer SHARED
    src/Debayer.cpp
    src/BMP.cpp
    include/Debayer.hpp
    include/BMP.hpp
    include/BMP_Headers.hpp
    )

add_executable(RAWtoPPM src/main.cpp)

target_link_libraries(RAWtoPPM PRIVATE Debayer)

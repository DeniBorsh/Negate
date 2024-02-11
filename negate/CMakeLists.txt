cmake_minimum_required(VERSION 3.11)

project(Negate CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(negate src/main.cpp src/img_lib.h src/img_lib.cpp src/ppm_image.h src/ppm_image.cpp) 
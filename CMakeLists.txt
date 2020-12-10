cmake_minimum_required(VERSION 3.17)
project(L3)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)
add_executable(L3 src/main.cpp src/shader.h src/camera.h)

target_link_libraries(L3 -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW)


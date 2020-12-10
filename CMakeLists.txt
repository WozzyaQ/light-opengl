cmake_minimum_required(VERSION 3.17)
project(L3)

set(Boost_USE_STATIC_LIBS OFF)
set(CMAKE_CXX_STANDARD 14)
include_directories(include)
add_executable(L3 src/main.cpp src/glad.c src/stb_image.h src/stb_image.cpp)

target_link_directories(L3 PRIVATE lib)
target_link_libraries(L3 -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl)
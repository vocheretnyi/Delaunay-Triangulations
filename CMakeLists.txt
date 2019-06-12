cmake_minimum_required(VERSION 3.13)
project(delaunay_triangulations)

set(CMAKE_CXX_STANDARD 17)

set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${PROJECT_INCLUDE_DIR})

add_executable(delaunay_triangulations main.cpp
        ${PROJECT_SOURCE_DIR}/DelaunayTriangulation.cpp
        ${PROJECT_SOURCE_DIR}/Circle.cpp
        ${PROJECT_SOURCE_DIR}/ConvexHull.cpp
)
target_link_libraries(delaunay_triangulations -lOpenGL32 -lfreeGLUT)
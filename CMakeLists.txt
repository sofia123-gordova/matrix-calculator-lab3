cmake_minimum_required(VERSION 3.20)

project(MatrixCalculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(matrix src/matrix.cpp)
target_include_directories(matrix PUBLIC include)
target_compile_options(matrix PRIVATE -Wall -Wextra)

add_executable(matrix_calculator src/main.cpp)
target_link_libraries(matrix_calculator PRIVATE matrix)

enable_testing()
add_subdirectory(tests)
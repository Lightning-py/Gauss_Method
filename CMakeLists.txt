cmake_minimum_required(VERSION 3.10)


project(MatrixCalculator)


include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)


add_executable(MatrixCalculator main.cpp matrix.hpp frac.hpp tools.hpp)
target_link_libraries(MatrixCalculator argparse)




cmake_minimum_required(VERSION 3.13)

project(rational)
enable_testing()


add_subdirectory(external)


add_library(rational INTERFACE)
target_compile_features(rational INTERFACE cxx_std_20)
target_include_directories(rational INTERFACE include)


add_subdirectory(tests)

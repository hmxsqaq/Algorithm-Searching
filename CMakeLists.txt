cmake_minimum_required(VERSION 3.29)
project(Algorithm_Searching)

set(CMAKE_CXX_STANDARD 20)

add_executable(Algorithm_Searching
        main.cpp
        comparable.h
        1_sequential_search_symbol_table.h
        2_binary_search_symbol_table.h
        3_red_black_bst.h)

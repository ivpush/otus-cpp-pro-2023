cmake_minimum_required(VERSION 3.5)

project(hw03-allocator)

add_executable(mine_allocator mine_allocator.cpp)
set_target_properties(mine_allocator PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)


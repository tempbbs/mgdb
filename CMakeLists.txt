cmake_minimum_required(VERSION 3.5.0)
project(mgdb VERSION 0.1.0 LANGUAGES C CXX)

find_package(ftxui REQUIRED)

add_executable(mgdb main.cpp gdbprocess.cpp)
add_executable(tui tui.cpp )
target_link_libraries(tui ftxui::screen ftxui::dom ftxui::component)




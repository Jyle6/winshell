cmake_minimum_required(VERSION 4.0.0)
project(WinShell LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(winshell winshell.c)
target_link_libraries(winshell PRIVATE
    user32
    gdi32
    kernel32
)
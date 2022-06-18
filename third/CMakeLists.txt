cmake_minimum_required(VERSION 3.10)

set(WARN_LIST -Wall -Wextra -pedantic -Wconversion -Wsign-conversion)

project(opt)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/TablePrinter/)

add_executable(opt src/opt.cc)
target_include_directories(opt PRIVATE include/ lib/TablePrinter/include)
target_link_libraries(opt TablePrinter)
target_compile_options(opt PRIVATE ${WARN_LIST})


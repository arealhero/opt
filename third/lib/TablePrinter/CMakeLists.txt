cmake_minimum_required(VERSION 3.0)

project(TablePrinter VERSION 1.0.0 DESCRIPTION "TablePrinter lib")

add_library(TablePrinter SHARED
	src/TablePrinter.cc)

set_target_properties(TablePrinter PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(TablePrinter PROPERTIES SOVERSION 1)

set_target_properties(TablePrinter PROPERTIES
	PUBLIC_HEADER include/TablePrinter.h)

target_include_directories(TablePrinter PRIVATE include)

# install(TARGETS TablePrinter
# 	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# 	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


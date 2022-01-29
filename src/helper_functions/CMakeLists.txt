cmake_minimum_required(VERSION 3.0.0)
project(helper_functions VERSION 1.0.0)

add_library(helper_functions STATIC helper_functions.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

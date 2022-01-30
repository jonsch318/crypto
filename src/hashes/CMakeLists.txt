cmake_minimum_required(VERSION 3.0.0)
project(hashes VERSION 1.0.0)

add_library(hashes STATIC md5.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

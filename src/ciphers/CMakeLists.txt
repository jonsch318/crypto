cmake_minimum_required(VERSION 3.0.0)
project(ciphers VERSION 1.0.0)

add_library(ciphers STATIC rsa.c xor.c)

target_include_directories(ciphers PUBLIC ${CMAKE_SOURCE_DIR}/include/ ${CMAKE_SOURCE_DIR}/src/extern/c-terminal/include/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

cmake_minimum_required(VERSION 3.0.0)
project(ciphers VERSION 1.0.0)

add_library(ciphers STATIC rsa.c xor.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

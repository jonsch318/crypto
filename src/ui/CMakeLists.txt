cmake_minimum_required(VERSION 3.0.0)
project(crypto_ui VERSION 1.0.0)

add_library(crypto_ui STATIC ui_menu.c ui_helper_functions.c ciphers/ui_rsa.c ciphers/ui_xor.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

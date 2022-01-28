cmake_minimum_required(VERSION 3.0.0)
project(crypto VERSION 1.0.0)

set(CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/cmake
    ${CMAKE_MODULE_PATH}
)

#add https://github.com/NilEis/C-Terminal
add_subdirectory(src/extern/c-terminal)
add_subdirectory(src/ui)
add_subdirectory(src/ciphers)
add_subdirectory(src/helper_functions)

find_package(GMP REQUIRED)

add_executable(crypto src/main.c)

target_link_libraries(crypto c-terminal ui ciphers helper_functions gmp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

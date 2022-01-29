cmake_minimum_required(VERSION 3.0.0)
project(crypto VERSION 1.0.0)

set(CMAKE_MODULE_PATH
    ${CMAKE_CURRENT_LIST_DIR}/cmake
    ${CMAKE_MODULE_PATH}
)

option(USE_GMP "Use gmp to support BigInt" ON)

#add https://github.com/NilEis/C-Terminal
add_subdirectory(src/extern/c-terminal)
add_subdirectory(src/ui)
add_subdirectory(src/ciphers)
add_subdirectory(src/helper_functions)

list(APPEND LIBS c_terminal)
list(APPEND LIBS crypto_ui)
list(APPEND LIBS ciphers)
list(APPEND LIBS helper_functions)
list(APPEND LIBS m)

if(USE_GMP)
    find_package(GMP REQUIRED)
    list(APPEND LIBS gmp)
    target_compile_definitions(crypto_ui PUBLIC USE_GMP)
    target_compile_definitions(ciphers PUBLIC USE_GMP)
    target_compile_definitions(helper_functions PUBLIC USE_GMP)
endif()

add_executable(crypto src/main.c)

target_link_libraries(crypto PUBLIC ${LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
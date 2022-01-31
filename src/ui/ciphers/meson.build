ui_ciphers_lib_src = files(
  'ui_rsa.c',
  'ui_xor.c'
)

ui_ciphers_lib = library('ui_ciphers', ui_ciphers_lib_src, link_with: [c_terminal_lib, helper_functions_lib, ciphers_lib], include_directories: [incdir, incdir_terminal])
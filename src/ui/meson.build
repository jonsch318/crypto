ui_lib_src = files(  
  'ui_menu.c', 
  'ui_helper_functions.c', 
)

subdir('ciphers')

ui_lib = library('ui', ui_lib_src, link_with: [c_terminal_lib, helper_functions_lib, ui_ciphers_lib], dependencies: [gmpDep, mDep], include_directories: [incdir, incdir_terminal])

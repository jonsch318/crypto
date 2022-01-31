#add https://github.com/NilEis/C-Terminal
# include_directories('../extern/c-terminal')

src = files(  
  'ui_menu.c', 
  'ui_helper_functions.c', 
  'ciphers/ui_rsa.c', 
  'ciphers/ui_xor.c'
)

ui_lib = library('ui', link_with: [c_terminal_lib, helper_functions_lib], dependencies: [gmpDep, mDep], include_directories: [incdir, incdir_terminal])
# target_link_libraries(['crypto_ui', 'c_terminal'])

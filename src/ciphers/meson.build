ciphers_lib_src = files(
  'rsa.c',
  'xor.c',
)

ciphers_lib = library('ciphers', ciphers_lib_src, dependencies: [gmpDep, mDep], include_directories: incdir)

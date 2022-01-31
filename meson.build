project('crypto', 'c', version: '0.0.1', license: 'MIT', default_options: ['default_library=static'])
cc = meson.get_compiler('c')

gmpDep = dependency('gmp', required: get_option('USE_GMP'), static: true)

if gmpDep.found() and get_option('USE_GMP')
  add_global_arguments('-DUSE_GMP=true', language: 'c')
endif

mDep = cc.find_library('m', required: true, static: true)

incdir = include_directories('include')

subdir('src')


crypto_bin_deps = [
  gmpDep, mDep
]

crypto_lib_deps = [
  ui_lib
]

executable('crypto', main_source, include_directories: incdir, dependencies: crypto_bin_deps, link_with: crypto_lib_deps)
project(
  'template-kindle-gtk',
  'cpp',
  version: 'v0.0.1',
  default_options: ['cpp_std=c++17'],
  meson_version: '>=1.1'
)

gtk_dep = dependency('gtk+-2.0')

sources = files(
  './src/main.cpp',
)

include_dirs = include_directories(
  './include/',
)

# `xxd -i` converts a binary file to a C header file
xxd_exe = find_program('xxd')
xxd_gen = generator(
  xxd_exe,
  output: '@PLAINNAME@.h',
  arguments: ['-i', '-C', '-n', '@PLAINNAME@', '@INPUT@', '@OUTPUT@']
)

gen_sources = xxd_gen.process(['src/main.ui.xml'])

executable(
  'template_kindle_gtk',
  sources + gen_sources,
  include_directories: include_dirs,
  dependencies: [
    gtk_dep,
  ],
  # https://kindlemodding.org/kindle-dev/gtk-tutorial/setting-up.html
  #   Koxtoolchain ships with a GCC version newer than the Kindle technically
  #   supports, but this is fine so long as we statically link the standard
  #   library.
  cpp_args: '-static-libstdc++',
  link_args: ['-static-libstdc++']
)

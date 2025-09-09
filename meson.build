project('paulista', 'cpp', version: '0.1.0', default_options : ['warning_level=3', 'cpp_std=c++23'])

sources       = []
headers       = include_directories('include')
dependencies  = []

paulista_dep = declare_dependency(
    include_directories : headers
  , dependencies        : dependencies
  )

if not meson.is_subproject()
  subdir('tests')
endif

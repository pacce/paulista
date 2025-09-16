project('paulista', 'cpp', version: '0.1.0', default_options : ['warning_level=3', 'cpp_std=c++23'])

sources       = [
    'source/paulista-dimension.cpp'
  , 'source/paulista-graph.cpp'
  , 'source/paulista-sparse.cpp'
  ]
headers       = include_directories('include')
dependencies  = []

paulista = library(
    'paulista'
  , sources
  , include_directories : headers
  , dependencies        : dependencies
  )

paulista_dep = declare_dependency(
    include_directories : headers
  , dependencies        : dependencies
  , link_with           : paulista
  )

if not meson.is_subproject()
  subdir('tests')
endif

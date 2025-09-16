cmake   = import('cmake')
options = cmake.subproject_options()
options.add_cmake_defines({'RC_ENABLE_GTEST': 'ON'})

rapidcheck_project  = cmake.subproject('rapidcheck', options: options)

rapidcheck          = rapidcheck_project.dependency('rapidcheck')
rapidcheck_gtest    = rapidcheck_project.dependency('rapidcheck_gtest')
gtest               = dependency('gtest')

dependencies  = [gtest, rapidcheck, rapidcheck_gtest, paulista_dep]

test(  'dimension', executable(  'dimension',   'dimension.cpp', dependencies: dependencies))
test(     'domain', executable(     'domain',      'domain.cpp', dependencies: dependencies))
test(     ' point', executable(      'point',       'point.cpp', dependencies: dependencies))
test(      'graph', executable(      'graph',       'graph.cpp', dependencies: dependencies))
test(   'triangle', executable(   'triangle',    'triangle.cpp', dependencies: dependencies))
test('tetrahedron', executable('tetrahedron', 'tetrahedron.cpp', dependencies: dependencies))

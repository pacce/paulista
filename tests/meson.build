cmake   = import('cmake')
options = cmake.subproject_options()
options.add_cmake_defines({'RC_ENABLE_GTEST': 'ON'})

rapidcheck_project  = cmake.subproject('rapidcheck', options: options)

rapidcheck          = rapidcheck_project.dependency('rapidcheck')
rapidcheck_gtest    = rapidcheck_project.dependency('rapidcheck_gtest')
gtest               = dependency('gtest')

dependencies  = [gtest, rapidcheck, rapidcheck_gtest, paulista_dep]

test(      'dimension', executable(      'dimension',       'dimension.cpp', dependencies: dependencies))
test(          'point', executable(          'point',           'point.cpp', dependencies: dependencies))
test(    'domain-area', executable(    'domain-area',     'domain-area.cpp', dependencies: dependencies))
test('domain-centroid', executable('domain-centroid', 'domain-centroid.cpp', dependencies: dependencies))
test( 'domain-visitor', executable( 'domain-visitor',  'domain-visitor.cpp', dependencies: dependencies))

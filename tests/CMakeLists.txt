enable_testing()

# Let unit tests include project headers
include_directories("${PROJECT_SOURCE_DIR}/src")

function(add_unit_test_suite target)
  add_executable(${target} ${ARGN})
  target_link_libraries(${target} boost_unit_test_framework)
  add_test(${target} ${target})
  set_target_properties(${target} PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_MODULE="${target}") 
endfunction()

function(add_gl_unit_test_suite target)
  add_executable(${target} ${ARGN})
  target_link_libraries(${target} GL GLEW SDL2 boost_unit_test_framework)
  add_test(${target} ${target})
  set_target_properties(${target} PROPERTIES COMPILE_DEFINITIONS BOOST_TEST_MODULE="${target}") 
endfunction()


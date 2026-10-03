cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

enable_testing()

set(REFRACT_TEST_SOURCES
    BasicTest.cpp
)

foreach(test_source IN LISTS REFRACT_TEST_SOURCES)
    get_filename_component(test_name "${test_source}" NAME_WE)
    add_executable(${test_name} "${test_source}")
    target_link_libraries(${test_name} PRIVATE refract)
    target_include_directories(${test_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_compile_features(${test_name} PRIVATE cxx_std_26)
    add_sanitizers(${test_name})
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

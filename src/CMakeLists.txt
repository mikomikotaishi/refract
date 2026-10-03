cmake_minimum_required(VERSION 3.28 FATAL_ERROR)

target_sources(refract
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/refract.cppm
)

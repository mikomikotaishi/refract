cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
message(STATUS "CMake version ${CMAKE_VERSION}")

set(REFRACT_CXX_STANDARD 26 CACHE INTERNAL "refract C++ standard (visible across directory scopes for FetchContent consumers)")
set(CMAKE_CXX_STANDARD ${REFRACT_CXX_STANDARD})
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_STATIC_LIBS "Build static libraries instead of shared" OFF)

option(REFRACT_ENABLE_SANITIZERS "Enable sanitizers in debug builds" OFF)
option(REFRACT_USE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
option(REFRACT_USE_SANITIZER_KERNEL "Enable kernel address sanitizer" OFF)
option(REFRACT_USE_SANITIZER_HW "Enable hardware address sanitizer" OFF)
option(REFRACT_USE_SANITIZER_UNDEFINED "Enable undefined behavior sanitizer" OFF)
option(REFRACT_USE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
option(REFRACT_USE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
option(REFRACT_USE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
option(REFRACT_BUILD_TESTS "Build tests" OFF)
option(REFRACT_BUILD_MODULE "Build the C++ module" OFF)

function(add_sanitizers target)
    if(NOT REFRACT_ENABLE_SANITIZERS)
        return()
    endif()

    if(COMPILER_GCC OR COMPILER_CLANG OR COMPILER_APPLE_CLANG)
        set(SANITIZER_FLAGS "")
        
        if(REFRACT_USE_SANITIZER_ADDRESS)
            list(APPEND SANITIZER_FLAGS "-fsanitize=address")
        endif()

        if(REFRACT_USE_SANITIZER_KERNEL)
            list(APPEND SANITIZER_FLAGS "-fsanitize=kernel-address")
        endif()

        if(REFRACT_USE_SANITIZER_HW)
            list(APPEND SANITIZER_FLAGS "-fsanitize=hwaddress")
        endif()

        if(REFRACT_USE_SANITIZER_UNDEFINED)
            list(APPEND SANITIZER_FLAGS "-fsanitize=undefined")
        endif()

        if(REFRACT_USE_SANITIZER_THREAD)
            list(APPEND SANITIZER_FLAGS "-fsanitize=thread")
        endif()

        if(REFRACT_USE_SANITIZER_MEMORY)
            list(APPEND SANITIZER_FLAGS "-fsanitize=memory")
        endif()
        
        if(REFRACT_USE_SANITIZER_LEAK)
            list(APPEND SANITIZER_FLAGS "-fsanitize=leak")
        endif()
        
        if(SANITIZER_FLAGS)
            target_compile_options(${target} PRIVATE ${SANITIZER_FLAGS})
            target_link_options(${target} PRIVATE ${SANITIZER_FLAGS})
        endif()
    endif()
endfunction()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NDEBUG)
    
    if(COMPILER_GCC OR COMPILER_CLANG OR COMPILER_APPLE_CLANG)
        add_compile_options(-O3)
    elseif(COMPILER_MSVC)
        add_compile_options(/O2)
    endif()
    
    set(ENABLE_SANITIZERS OFF)
endif()

add_library(refract INTERFACE)

target_include_directories(refract INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(refract INTERFACE cxx_std_26)

include(CheckCXXCompilerFlag)
set(CMAKE_REQUIRED_FLAGS "-std=c++26")
check_cxx_compiler_flag("-freflection" REFRACT_HAS_FREFLECTION)
unset(CMAKE_REQUIRED_FLAGS)
if(REFRACT_HAS_FREFLECTION)
    target_compile_options(refract INTERFACE $<$<COMPILE_LANGUAGE:CXX>:-freflection>)
endif()

if(REFRACT_BUILD_MODULE)
    add_subdirectory(src)
endif()

if(REFRACT_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_sanitizers(refract)

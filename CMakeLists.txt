cmake_minimum_required(VERSION 3.25)

project(
    dsa_cpp
    VERSION 0.1.0
    DESCRIPTION "Data Structures and Algorithms in Modern C++"
    LANGUAGES CXX
)

# ------------------------------------------------------------
# C++ standard
# ------------------------------------------------------------

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ------------------------------------------------------------
# Build options
# ------------------------------------------------------------

option(DSA_ENABLE_WARNINGS "Enable compiler warnings" ON)
option(DSA_ENABLE_TESTS "Enable unit tests" OFF)

# ------------------------------------------------------------
# Main library
# ------------------------------------------------------------

add_library(dsa_cpp
    src/algorithms/insertion_sort.cpp
    src/algorithms/insertion_sort_inv.cpp
    src/algorithms/linear_search.cpp
    src/algorithms/selection_sort.cpp
    src/algorithms/merge_sort.cpp
    include/utils/print_utils.hpp
    src/algorithms/find_maximum_subarray.cpp
    src/algorithms/find_maximum_subarray_brute_force.cpp
    src/algorithms/square_matrix_multiply.cpp
    src/algorithms/square_matrix_multiply_recursive.cpp
    src/algorithms/square_matrix_multiply_strassen.cpp
    src/data_structures/stack.cpp
    src/data_structures/queue.cpp
    src/data_structures/linked_list.cpp
    src/data_structures/circular_linked_list.cpp
    src/data_structures/direct_access_table.cpp
    src/data_structures/static_hash_chained_table.cpp
    src/data_structures/universal_hash_chained_table.cpp
    src/data_structures/open_addressing_hash_table.cpp
)

target_include_directories(dsa_cpp
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(dsa_cpp
    PUBLIC
        cxx_std_23
)

# ------------------------------------------------------------
# Compiler warnings
# ------------------------------------------------------------

if(DSA_ENABLE_WARNINGS)
    if(MSVC)
        target_compile_options(dsa_cpp PRIVATE /W4 /permissive-)
    else()
        target_compile_options(dsa_cpp PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wshadow
        )
    endif()
endif()

# ------------------------------------------------------------
# Main executable
# ------------------------------------------------------------

add_executable(dsa_app
    app/main.cpp
)

target_link_libraries(dsa_app
    PRIVATE
        dsa_cpp
)

# ------------------------------------------------------------
# Tests
# ------------------------------------------------------------

if(DSA_ENABLE_TESTS)
    enable_testing()

    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.1
    )

    FetchContent_MakeAvailable(Catch2)

    add_executable(dsa_tests
        # tests/algorithms/insertion_sort_tests.cpp
        # tests/algorithms/insertion_sort_array_tests.cpp
        # tests/algorithms/insertion_sort_inv_tests.cpp
        # tests/algorithms/linear_search_tests.cpp
        # tests/algorithms/selection_sort_tests.cpp
        # tests/algorithms/merge_sort_tests.cpp
        # tests/algorithms/find_maximum_subarray_tests.cpp
        # tests/algorithms/find_maximum_subarray_brute_force_tests.cpp
        # tests/algorithms/square_matrix_multiply_tests.cpp
        # tests/algorithms/square_matrix_multiply_recursive_tests.cpp
        # tests/algorithms/square_matrix_multiply_strassen_tests.cpp
        # tests/data_structures/stack_tests.cpp
        # tests/data_structures/queue_tests.cpp
        # tests/data_structures/linked_list_tests.cpp
        # tests/data_structures/circular_linked_list_tests.cpp
        # tests/data_structures/direct_access_table_tests.cpp
        # tests/data_structures/static_hash_chained_table_tests.cpp
        # tests/data_structures/universal_hash_chained_table_tests.cpp
        tests/data_structures/open_addressing_hash_table_tests.cpp
    )

    target_link_libraries(dsa_tests
        PRIVATE
            dsa_cpp
            Catch2::Catch2WithMain
    )

    include(CTest)
    include(Catch)

    catch_discover_tests(dsa_tests)
endif()

# ------------------------------------------------------------
# Experiments
# ------------------------------------------------------------

add_executable(dsa_experiments
    # experiments/algorithms/maximum_subarray_benchmark.cpp
    experiments/data_structures/stl_hash_examples.cpp
)

target_link_libraries(dsa_experiments
    PRIVATE
        dsa_cpp
)
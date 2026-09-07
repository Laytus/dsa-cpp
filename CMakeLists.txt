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
    # src/algorithms/insertion_sort.cpp
    src/algorithms/insertion_sort_inv.cpp
    src/algorithms/linear_search.cpp
    src/algorithms/selection_sort.cpp
    src/algorithms/merge_sort.cpp
    # include/utils/print_utils.hpp
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
    src/algorithms/heap_sort.cpp
    src/data_structures/max_priority_queue.cpp
    src/data_structures/min_priority_queue.cpp
    src/algorithms/quick_sort.cpp
    src/algorithms/counting_sort.cpp
    src/algorithms/radix_sort.cpp
    src/algorithms/bucket_sort.cpp
    src/algorithms/randomized_select.cpp
    src/algorithms/select.cpp
    src/data_structures/binary_search_tree.cpp
    src/data_structures/red_black_tree.cpp
    src/data_structures/order_statistic_tree.cpp
    src/data_structures/interval_tree.cpp
    src/data_structures/disjoint_set_forest.cpp
    src/algorithms/longest_common_subsequence.cpp
    src/algorithms/optimal_BST.cpp
    src/algorithms/activity_selector.cpp
    src/algorithms/huffman_codes.cpp
    # include/algorithms/rectangular_matrix_multiply.hpp
    src/data_structures/adjacency_list_graph.cpp
    src/algorithms/breadth_first_search.cpp
    src/algorithms/depth_first_search.cpp
    src/algorithms/topological_sort.cpp
    src/algorithms/strongly_connected_components.cpp
    src/algorithms/minimum_spanning_tree.cpp
    src/data_structures/weighted_adjacency_list_graph.cpp
    src/algorithms/single_source_shortest_paths.cpp
    src/algorithms/bellman_ford.cpp
    src/algorithms/dag_shortest_paths.cpp
    src/algorithms/dijkstra.cpp
    src/algorithms/all_pair_shortest_paths.cpp
    src/algorithms/johnson_apsp.cpp
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
        tests/algorithms/insertion_sort_tests.cpp
        tests/algorithms/insertion_sort_array_tests.cpp
        tests/algorithms/insertion_sort_inv_tests.cpp
        tests/algorithms/linear_search_tests.cpp
        tests/algorithms/selection_sort_tests.cpp
        tests/algorithms/merge_sort_tests.cpp
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
        # tests/data_structures/open_addressing_hash_table_tests.cpp
        # tests/algorithms/heap_sort_tests.cpp
        # tests/data_structures/max_priority_queue_tests.cpp
        # tests/data_structures/min_priority_queue_tests.cpp
        # tests/algorithms/quick_sort_tests.cpp
        # tests/algorithms/counting_sort_tests.cpp
        # tests/algorithms/radix_sort_tests.cpp
        # tests/algorithms/bucket_sort_tests.cpp
        # tests/algorithms/minimum_maximum_tests.cpp
        # tests/algorithms/randomized_select_tests.cpp
        # tests/algorithms/select_tests.cpp
        # tests/data_structures/binary_search_tree_tests.cpp
        # tests/data_structures/red_black_tree_tests.cpp
        # tests/data_structures/order_statistic_tree_tests.cpp
        # tests/data_structures/interval_tree_tests.cpp
        # tests/data_structures/disjoint_set_forest_tests.cpp
        # tests/algorithms/matrix_chain_tests.cpp
        # tests/algorithms/longest_common_subsequence_tests.cpp
        # tests/algorithms/optimal_BST_tests.cpp
        # tests/algorithms/huffman_codes_tests.cpp
        # tests/algorithms/breadth_first_search_tests.cpp
        # tests/algorithms/depth_first_search_tests.cpp
        # tests/algorithms/topological_sort_tests.cpp
        # tests/algorithms/strongly_connected_components_tests.cpp
        # tests/algorithms/minimum_spanning_tree_tests.cpp
        # tests/algorithms/single_source_shortest_paths_tests.cpp
        # tests/data_structures/weighted_adjacency_list_graph_tests.cpp
        # tests/algorithms/bellman_ford_tests.cpp
        # tests/algorithms/dag_shortest_paths_tests.cpp
        # tests/algorithms/dijkstra_tests.cpp
        # tests/algorithms/all_pair_shortest_paths_tests.cpp
        tests/algorithms/johnson_apsp_tests.cpp
    )

    target_link_libraries(dsa_tests
        PRIVATE
            dsa_cpp
            Catch2::Catch2WithMain
    )

    # include(CTest)
    # include(Catch)

    # catch_discover_tests(dsa_tests)
    add_test(NAME dsa_tests COMMAND dsa_tests)
endif()

# ------------------------------------------------------------
# Experiments
# ------------------------------------------------------------

add_executable(dsa_experiments
    app/experiment_runner.cpp
    experiments/algorithms/maximum_subarray_benchmark.cpp
    experiments/data_structures/stl_hash_examples.cpp
    experiments/data_structures/stl_priority_queue_examples.cpp
    experiments/data_structures/stl_tree_examples.cpp
    experiments/algorithms/activity_selector_comparison.cpp
    experiments/algorithms/huffman_codes_comparison.cpp
)

target_link_libraries(dsa_experiments
    PRIVATE
        dsa_cpp
)

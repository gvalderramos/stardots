add_executable(nodal_lib_test
    node_test.cpp
)

target_include_directories(nodal_lib_test PRIVATE ${googletest_SOURCE_DIR}/googletest/include)
target_link_libraries(nodal_lib_test PRIVATE gtest_main nodal_lib)
add_executable(nodal_lib_test
        plug_test.cpp
        node_test.cpp
        node_manager_test.cpp
)

target_include_directories(nodal_lib_test PRIVATE ${googletest_SOURCE_DIR}/googletest/include)
target_include_directories(nodal_lib_test PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(nodal_lib_test PRIVATE gtest_main StarDots)
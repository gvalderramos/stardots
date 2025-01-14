include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_GetProperties(googletest)

enable_testing()

add_executable(startdot_test
        plug_test.cpp
        node_test.cpp
        node_manager_test.cpp
)

target_include_directories(startdot_test PRIVATE ${googletest_SOURCE_DIR}/googletest/include)
target_include_directories(startdot_test PRIVATE ${PROJECT_SOURCE_DIR}/lib)
target_link_libraries(startdot_test PRIVATE gtest_main StarDots)
include(GoogleTest)
gtest_discover_tests(startdot_test)

project(system-server  LANGUAGES CXX)
find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)

enable_testing()

add_executable(system_server ./include/system/system.h ./src/system.cpp)

add_executable(system_server_test ./test/test.cpp/)
target_include_directories(system_server PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(system_server PUBLIC nlohmann_json_LIBRARIES)
target_link_libraries(system_server_test PRIVATE
        GTest::gtest GTest::gmock GTest::gtest_main )
target_link_libraries(system_server PUBLIC simple_detector rtlsdr_control)

add_test(NAME system_server COMMAND system_server_test)

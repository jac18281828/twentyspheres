cmake_minimum_required(VERSION 3.9)

project(${PROJECT_NAME} LANGUAGES CXX VERSION 1.0.0)

add_compile_options(-std=c++20)

set(HDR include/color.h include/cube.h include/image.h include/patch.h
include/render.h include/spatial.h include/tripple.h include/twenty.h
include/twmath.h include/vertex.h include/bitmap.h)

set(SRC src/main.cpp)

add_executable(${PROJECT_NAME} ${HDR} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} jpeg m)

#find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        twenty_test
        ${HDR}
        test/twenty_test.cpp
        test/tripple_test.cpp
        test/twmath_test.cpp
        test/vertex_test.cpp
        test/patch_test.cpp
        test/cube_test.cpp
        test/bitmap_test.cpp
)
target_include_directories(twenty_test PRIVATE include)
target_link_libraries(
  twenty_test
  gtest_main
  jpeg
  m
)

include(GoogleTest)
gtest_discover_tests(twenty_test)


cmake_minimum_required(VERSION 3.0)
project(cmake_example CXX)

find_package(GTest REQUIRED)
add_executable(mytest example.cpp example_test.cpp)
target_link_libraries(mytest
  PRIVATE
    GTest::GTest
    GTest::Main   # GTest::Mainをリンクすると自分でmain関数を書く必要がなくなる
  )
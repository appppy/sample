cmake_minimum_required(VERSION 3.0)
project(cmake_example CXX)

find_package(GTest REQUIRED)
add_executable(mytest example.cpp example_test.cpp)
target_link_libraries(mytest
  PRIVATE
    GTest::GTest
    GTest::Main   # GTest::Main‚ğƒŠƒ“ƒN‚·‚é‚Æ©•ª‚ÅmainŠÖ”‚ğ‘‚­•K—v‚ª‚È‚­‚È‚é
  )
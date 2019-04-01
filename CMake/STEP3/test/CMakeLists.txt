add_executable(a.out main.cpp)
# a.outをコンパイルする際にgreetingsをリンクする
target_link_libraries(a.out greetings)
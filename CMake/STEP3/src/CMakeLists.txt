add_library(greetings
  SHARED
    hello.cpp
    good_morning.cpp
  )
# greetingライブラリのインクルードディレクトリを教えてあげる
# PROJECT_SOURCE_DIRはこのプロジェクトのルートディレクトリの絶対パス
target_include_directories(greetings
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )

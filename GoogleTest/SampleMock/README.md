Build & Run
===========

```
$ g++ -std=c++11 test/example_test.cpp -I. -Isrc -Igoogletest/include -Lgoogletest -lgtest -lgtest_main -lgmock -lgmock_main -lpthread
$ ./a.out
```

cmake_minimum_required(VERSION 3.10)
project(simpleIndex)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(~/Downloads/mysql-connector-c++-8.0.18-linux-glibc2.12-x86-64bit/include/jdbc)

link_libraries(-lmysqlcppconn)


add_executable(simpleIndex
        include/mysql.h
        include/onebar.h
        include/symbol.h
        include/EnvelopGen.h
        include/binarySearchTree.h
        include/breakpoints.h
        include/iSax.h
        src/main.C
        src/mysql.C
        src/onebar.C
        src/symbol.C
        src/iSax.cpp
        src/EnvelopGen.cpp
        src/breakpoints.cpp
        src/binarySearchTree.cpp
        src/syntheticData.cpp include/syntheticData.h)

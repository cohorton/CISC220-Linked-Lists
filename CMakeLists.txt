cmake_minimum_required(VERSION 3.27)
project(DLLTaskManager_1__1_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DLLTaskManager_1__1_
        DLL.cpp
        DLL.hpp
        DNode.cpp
        DNode.hpp
        MainDLL.cpp
        Task.cpp
        Task.hpp
        TaskManager.cpp
        TaskManager.hpp)

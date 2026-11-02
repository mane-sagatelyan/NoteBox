cmake_minimum_required(VERSION 3.30)
project(NoteBox)

set(CMAKE_CXX_STANDARD 20)

add_executable(notebox
        main.cpp
        Notebox.cpp
        Notebox.h
        Shared_mem.h)

find_package(Threads REQUIRED)
target_link_libraries(notebox PRIVATE Threads::Threads rt)
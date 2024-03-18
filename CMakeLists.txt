cmake_minimum_required(VERSION 3.11-3.18)


project(
        main
        VERSION 1.0
        DESCRIPTION "Build main")

set(SOURCES src/main.cpp src/glad.c src/square.cpp) 

add_executable(main ${SOURCES})
target_link_libraries(main -lglfw3)
if (WIN32)
    target_link_libraries(main -lgdi32)
endif()
target_include_directories(main PRIVATE include/)
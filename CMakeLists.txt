cmake_minimum_required(VERSION 3.11-3.18)


project(
        main
        VERSION 1.0
        DESCRIPTION "Build main")

set(SOURCES src/main.cpp src/glad.c src/square.cpp) 

add_executable(main ${SOURCES})
target_link_libraries(main -L${CMAKE_CURRENT_LIST_DIR}/lib)

if (WIN32)
    target_link_libraries(main -lgdi32)
    target_link_libraries(main -lglfw3WIN)
endif(WIN32)

if (UNIX)
    target_link_libraries(main -lglfw32)
endif (UNIX)
target_include_directories(main PRIVATE include/)
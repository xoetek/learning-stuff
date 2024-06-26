cmake_minimum_required(VERSION 3.11-3.18)


project(
        main
        VERSION 1.0
        DESCRIPTION "Build main")

set(SOURCES src/main.cpp src/glad.c src/square.cpp src/shader.cpp src/stb_image.cpp) 

add_executable(main ${SOURCES})
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    SET_TARGET_PROPERTIES(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
    target_link_libraries(main -L${CMAKE_CURRENT_LIST_DIR}/lib)
    if (WIN32)
        target_link_libraries(main -lgdi32)
        target_link_libraries(main -lglfw3WIN)
    elseif (UNIX)
        target_link_libraries(main -lglfw3)
    endif ()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    SET_TARGET_PROPERTIES(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin)
    SET_TARGET_PROPERTIES(main PROPERTIES LINK_FLAGS "/NODEFAULTLIB:MSVCRT")
    target_link_libraries(main ${CMAKE_CURRENT_LIST_DIR}/lib/glfw3.lib)
    target_link_libraries(main gdi32)
endif()
target_include_directories(main PRIVATE include/)
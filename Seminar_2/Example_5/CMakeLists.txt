cmake_minimum_required(VERSION 3.1)

get_filename_component(DIR_NAME "${CMAKE_CURRENT_LIST_DIR}" NAME)
project(${DIR_NAME})

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

include_directories(inc/)

set(HELLO_HEADER_FILES
        inc/Utility/Clock.hpp)
set(HELLO_SOURCE_FILES
        src/Utility/Clock.cpp)
set(MAIN_FILE
        src/main.cpp)

add_executable(${PROJECT_NAME}
               ${HELLO_HEADER_FILES}
               ${HELLO_SOURCE_FILES}
               ${MAIN_FILE})

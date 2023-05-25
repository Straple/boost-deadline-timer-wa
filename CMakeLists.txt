cmake_minimum_required(VERSION 3.23)

project(sportprog)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost COMPONENTS date_time regex chrono)

IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    add_executable(sportprog main.cpp)

    target_link_libraries(sportprog ${Boost_LIBRARIES})

ENDIF()

cmake_minimum_required(VERSION 3.1)
project(crow-hello-world)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()

if (MSVC)
    set(Boost_USE_STATIC_LIBS "On")
    find_package(Boost 1.63 COMPONENTS date_time filesystem system thread regex REQUIRED)
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++1y")
    find_package(Boost 1.63 COMPONENTS date_time filesystem system thread REQUIRED)
endif ()

find_package(Threads)
include_directories(${Boost_INCLUDE_DIR})

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}")
message(STATUS "Boost_VERSION: ${Boost_VERSION}")

add_executable(app main.cpp)

if (Tcmalloc_FOUND)
    target_link_libraries(app ${Tcmalloc_LIBRARIES})
endif (Tcmalloc_FOUND)
target_link_libraries(app ${Boost_LIBRARIES})
target_link_libraries(app ${CMAKE_THREAD_LIBS_INIT})

add_custom_command(OUTPUT index.html
        COMMAND ${CMAKE_COMMAND} -E
        copy ${PROJECT_SOURCE_DIR}/index.html ${CMAKE_CURRENT_BINARY_DIR}/index.html
        DEPENDS ${PROJECT_SOURCE_DIR}/index.html
        )
add_custom_target(app_copy ALL DEPENDS index.html)

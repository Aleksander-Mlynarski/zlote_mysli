cmake_minimum_required(VERSION 3.13)

set(PROJECT_ID zlote_mysli)
project(${PROJECT_ID})

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include(SetCommonConfig.cmake)

add_executable(${PROJECT_ID} ${SOURCE_FILES} ${HEADER_FILES})
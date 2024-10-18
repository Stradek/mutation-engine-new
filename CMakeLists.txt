#
# Copyright (c) 2024 Piotr Stradowski. All rights reserved.
# Software distributed under the permissive MIT License.
#

#
# Project Info
#

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
cmake_policy(VERSION 3.9)

include(CMake/CMakeShared.cmake)

#
# Project
#

project(MutationEngine-Pong)

# Setting up custom properties and functions from "CMakeShared.cmake" file
custom_cmake_setup()

#
# Output Directories
#

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

#
# Directories paths
#

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dev/src)
set(EXTERNAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external)

#
# Common
#
set(COMMON_DIR ${SOURCE_DIR}/common)

get_source_files(COMMON_SOURCE_FILES 1 ${COMMON_DIR})
add_library(Common STATIC
    "${COMMON_SOURCE_FILES}"
)
target_include_directories(Common PRIVATE
    ${COMMON_DIR}
)

#
# MutationEngine
#

set(ENGINE_DIR ${SOURCE_DIR}/engine)

get_source_files(ENGINE_SOURCE_FILES 1 ${ENGINE_DIR})
add_library(MutationEngine STATIC
    "${ENGINE_SOURCE_FILES}"
)
target_include_directories(MutationEngine PRIVATE
    ${ENGINE_DIR}
    ${COMMON_DIR}
)

target_link_libraries(MutationEngine PUBLIC 
    Common
)


# Link SDL2 libraries
target_link_libraries(MutationEngine PRIVATE
    "${EXTERNAL_PATH}/SDL2/lib/SDL2.lib"
    "${EXTERNAL_PATH}/SDL2/lib/SDL2main.lib"
)

# Include SDL2 headers
target_include_directories(MutationEngine PUBLIC
    "${EXTERNAL_PATH}/SDL2/include/"
)

#
# Game
#

set(GAME_DIR ${SOURCE_DIR}/game)

get_source_files(GAME_SOURCE_FILES 1 ${GAME_DIR})
add_executable(Pong ${GAME_SOURCE_FILES})
target_include_directories(Pong PRIVATE 
    ${COMMON_DIR}
    ${ENGINE_DIR}
    ${GAME_DIR}
)

target_link_libraries(Pong PRIVATE 
    MutationEngine
)

# Copy SDL2.dll to the output directory
add_custom_command(TARGET Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${EXTERNAL_PATH}/SDL2/lib/SDL2.dll"
    $<TARGET_FILE_DIR:Pong>
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Pong)
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

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(EXTERNAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external)

# Game
get_source_files(SOURCE_FILES 1 ${SOURCE_DIR})
add_executable(MutationEngine-Pong "${SOURCE_FILES}")
target_include_directories(MutationEngine-Pong PRIVATE ${SOURCE_DIR})

############################################
# SDL2
############################################

# Link SDL2 libraries
target_link_libraries(MutationEngine-Pong PRIVATE
    "${EXTERNAL_PATH}/SDL2/lib/SDL2.lib"
    "${EXTERNAL_PATH}/SDL2/lib/SDL2main.lib"
)

# Include SDL2 headers
target_include_directories(MutationEngine-Pong PRIVATE
    "${EXTERNAL_PATH}/SDL2/include/"
)

# Copy SDL2.dll to the output directory
add_custom_command(TARGET MutationEngine-Pong POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${EXTERNAL_PATH}/SDL2/lib/SDL2.dll"
    $<TARGET_FILE_DIR:MutationEngine-Pong>
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MutationEngine-Pong)
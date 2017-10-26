cmake_minimum_required(VERSION 3.9)
# Compiler flags
if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /EHsc" CACHE INTERNAL "" FORCE)
endif(MSVC)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Astral_Insanity)

#### Setup Directories ####
#Main output directory
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/bin")
SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")
SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")
# Ouput all DLLs from all libs into main build folder

add_subdirectory("lib/sfml")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
add_executable(Astral_Insanity_main ${SOURCE_FILES})

target_link_libraries(Astral_Insanity_main PRIVATE sfml-graphics sfml-audio)
target_include_directories(Astral_Insanity_main PRIVATE "lib/sfml/include")

add_custom_target(
        copy_resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
)

add_dependencies(Astral_Insanity_main copy_resources)

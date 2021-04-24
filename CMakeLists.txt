cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)


project(CPP_fingerprint_generator
    VERSION "1.0.0"
    DESCRIPTION "audio fingerprinting lib"
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs")


#allow to use std::experimental::filesystem
link_libraries(stdc++fs) 

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

set(INCLUDES
    "${CMAKE_CURRENT_SOURCE_DIR}/includes"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    ${DEPENDENCIES_HEADERS}
)

SET(LIBRARIES
    dejavu_cpp_port
    cpp_cannonical_wav_decoder
    minimp3
)

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDES})

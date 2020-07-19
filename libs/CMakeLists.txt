#./libs/CMakeLists.txt

set(BUILD_SHARED_LIBS OFF)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/cpp-canonical-wav-decoder")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dejavu_cpp_port")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/minimp3")





set(DEPENDENCIES_HEADERS
"${CMAKE_CURRENT_SOURCE_DIR}/cpp-canonical-wav-decoder/include"
"${CMAKE_CURRENT_SOURCE_DIR}/dejavu_cpp_port/include"
"${CMAKE_CURRENT_SOURCE_DIR}/minimp3"
  PARENT_SCOPE
)



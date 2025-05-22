cmake_minimum_required(VERSION 3.15)
project(GLog)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

option(GLOG_BUILD_TESTS "Build GLog test executable" OFF)

file(GLOB SUBMODULES "external/*")

foreach(SUBMODULE ${SUBMODULES})
  if(IS_DIRECTORY ${SUBMODULE})
    if(EXISTS "${SUBMODULE}/CMakeLists.txt")
      message(STATUS "Adding submodule: ${SUBMODULE}")
      add_subdirectory(${SUBMODULE})
    endif()
  endif()
endforeach()

add_subdirectory(src)

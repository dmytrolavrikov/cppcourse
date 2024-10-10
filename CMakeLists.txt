cmake_minimum_required(VERSION 3.10)

project(cppcourse)

find_library(GTest
             NAMES GTest
             HINTS "${CMAKE_CURRENT_LIST_DIR}/thirdparty/gtest")

include_directories(${PROJECT_NAME}
  include
)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
)

add_subdirectory(test)
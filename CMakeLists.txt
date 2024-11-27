cmake_minimum_required(VERSION 3.10)

project(cppcourse)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

include_directories(${PROJECT_NAME}
  PUBLIC
  include
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
)

add_subdirectory(test)
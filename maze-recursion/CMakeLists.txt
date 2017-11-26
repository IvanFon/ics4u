cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(maze-recursion)

# C++11
set(CMAKE_CXX_STANDARD 11)

# Options
option(CPPLINT "Run cpplint on code" YES)

# pkg-config
find_package(PkgConfig REQUIRED)

# Allegro
pkg_search_module(ALLEGRO REQUIRED allegro-5)
pkg_search_module(ALLEGRO_PRIMITIVES REQUIRED allegro_primitives-5)

# Get sources
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# cpplint
set(CMAKE_CXX_CPPLING
  cpplint
  --linelength=120
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
  PRIVATE ${PROJECT_SOURCE_DIR}/inc
  PUBLIC ${PROJECT_SOURCE_DIR}/inc
  PUBLIC ${ALLEGRO_INCLUDE_DIRS}
  PUBLIC ${ALLEGRO_PRIMITIVES_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  ${ALLEGRO_LIBRARIES}
  ${ALLEGRO_PRIMITIVES_LIBRARIES}
)

# Copy resources
file(COPY
  ${PROJECT_SOURCE_DIR}/res
  DESTINATION ${CMAKE_BINARY_DIR}
)

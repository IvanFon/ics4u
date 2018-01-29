cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(sorting)

# C++11
set(CMAKE_CXX_STANDARD 11)

# Options
option(CPPLINT "Run cpplint on code" YES)

# pkg-config
find_package(PkgConfig REQUIRED)

# Allegro
pkg_search_module(ALLEGRO REQUIRED allegro-5)
pkg_search_module(ALLEGRO_PRIMITIVES REQUIRED allegro_primitives-5)
pkg_search_module(ALLEGRO_FONT REQUIRED allegro_font-5)
pkg_search_module(ALLEGRO_TTF REQUIRED allegro_ttf-5)
pkg_search_module(ALLEGRO_DIALOG REQUIRED allegro_dialog-5)

# Get source files
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# cpplint
set(CMAKE_CXX_CPPLINT
  cpplint
  --filter=-legal/copyright,-runtime/references,-build/c++11,-readability/casting,-build/include_order,-runtime/int
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
  PRIVATE ${PROJECT_SOURCE_DIR}/inc
  PUBLIC ${ALLEGRO_INCLUDE_DIRS}
  PUBLIC ${ALLEGRO_PRIMITIVES_INCLUDE_DIRS}
  PUBLIC ${ALLEGRO_DIALOG_INCLUDE_DIRS}
  PUBLIC ${ALLEGRO_FONT_INCLUDE_DIRS}
  PUBLIC ${ALLEGRO_TTF_INCLUDE_DIRS}
  PUBLIC ${ALLEGRO_DIALOG_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
  ${ALLEGRO_LIBRARIES}
  ${ALLEGRO_PRIMITIVES_LIBRARIES}
  ${ALLEGRO_DIALOG_LIBRARIES}
  ${ALLEGRO_FONT_LIBRARIES}
  ${ALLEGRO_TTF_LIBRARIES}
  ${ALLEGRO_DIALOG_LIBRARIES}
)

# Copy resources
file(COPY
  ${PROJECT_SOURCE_DIR}/res/
  DESTINATION ${CMAKE_BINARY_DIR}/res/
)

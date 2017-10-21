cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(merge)

# C++11
set(CMAKE_CXX_STANDARD 11)

# Options
option(CPPLINT "Run cpplint on code" YES)

# Get source files
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# cpplint
set(CMAKE_CXX_CPPLINT
  cpplint
  --filter=-legal/copyright,-runtime/references,-runtime/string
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Copy resources
file(COPY
  ${PROJECT_SOURCE_DIR}/res/
  DESTINATION ${CMAKE_BINARY_DIR}
)

cmake_minimum_required(VERSION 2.8.5)

set(PROJECT_NAME Graph)
set(TARGET_NAME ${PROJECT_NAME})
set(INCLUDE_PATH "include")
set(SRC_PATH "src")

project(${PROJECT_NAME})

file(GLOB SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SRC_PATH}/*.cpp")

include_directories(${INCLUDE_PATH})

add_executable(
	${TARGET_NAME}
	${SRC}
)


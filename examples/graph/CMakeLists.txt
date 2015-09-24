cmake_minimum_required(VERSION 2.8.5)

project("graph")

set(TARGET ${PROJECT_NAME})
set(TARGET_INCLUDE_PATH "include")
set(TARGET_SRC_PATH "src")
set(TARGET_RES_PATH "res")
set(TARGET_LINK_LIBS sgl)

include_directories(${TARGET_INCLUDE_PATH})

add_compile_options(-std=c++11)

file(GLOB SRC "${TARGET_SRC_PATH}/*.cpp")

add_executable(${TARGET} ${SRC})

target_link_libraries(
    ${TARGET}
    ${TARGET_LINK_LIBS}
)

file(COPY "${TARGET_RES_PATH}/file.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

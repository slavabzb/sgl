cmake_minimum_required(VERSION 2.8.5)

set(INCLUDE_PATH "include")
set(SRC_PATH "src")
set(LINK_LIBS sgl)

project("graph")

include_directories(${INCLUDE_PATH})

add_compile_options(-std=c++11)

file(GLOB SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SRC_PATH}/*.cpp")

set(TARGET "${EXAMPLES_PREFIX}${PROJECT_NAME}${EXAMPLES_POSTFIX}")

add_executable(${TARGET} ${SRC})

target_link_libraries(
    ${TARGET}
    ${LINK_LIBS}
)

file(COPY "res/file.txt" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

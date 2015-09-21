cmake_minimum_required(VERSION 2.8.5)

set(PROJECT_NAME sgl)
set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "1")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

set(LIB_NAME ${PROJECT_NAME})
set(LIB_INSTALL_PATH lib)
set(INCLUDE_PATH "include")
set(SRC_PATH "src")
set(CMAKE_MODULE_PATH "cmake")
set(FAKEIT_MODULE_PATH "FakeIt")
set(LINK_LIBS )

project(${PROJECT_NAME})

include_directories(${INCLUDE_PATH})
include_directories(${FAKEIT_MODULE_PATH}/include)
include_directories(${FAKEIT_MODULE_PATH}/single_header/standalone)

add_compile_options(-std=c++11)

file(GLOB SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SRC_PATH}/*.cpp")

add_library(
    ${LIB_NAME} SHARED
    ${SRC}
)

target_link_libraries(
    ${LIB_NAME}
    ${LINK_LIBS}
)

if(BUILD_TESTS)
    include(${CMAKE_MODULE_PATH}/tests/build.cmake)
endif()

if(BUILD_EXAMPLES)
    include(${CMAKE_MODULE_PATH}/examples/build.cmake)
endif()

install(TARGETS ${LIB_NAME}
    LIBRARY DESTINATION ${LIB_INSTALL_PATH}
    PERMISSIONS 
    OWNER_WRITE OWNER_READ OWNER_EXECUTE
    GROUP_WRITE GROUP_READ OWNER_EXECUTE
    WORLD_READ
)

add_custom_target(uninstall
    COMMAND "${CMAKE_COMMAND}" -DINSTALL_DIR=${CMAKE_INSTALL_PREFIX} -P
    "${CMAKE_CURRENT_SOURCE_DIR}/${CMAKE_MODULE_PATH}/project/uninstall.cmake")

cmake_minimum_required(VERSION 2.8.5)

project(sgl)

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "5")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

set(TARGET "${PROJECT_NAME}")
set(TARGET_INSTALL_PATH "lib")
set(TARGET_INCLUDE_PATH "include")
set(TARGET_SRC_PATH "src")
set(TARGET_LINK_LIBS )

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(FAKEIT_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/FakeIt")

set(LIBRARY_OUTPUT_PATH "lib")

include_directories(${TARGET_INCLUDE_PATH})
include_directories(${FAKEIT_MODULE_PATH}/include)
include_directories(${FAKEIT_MODULE_PATH}/single_header/standalone)

add_compile_options(-std=c++11)
add_compile_options(-Wall)

file(GLOB TARGET_SRC "${TARGET_SRC_PATH}/*.cpp")
file(GLOB VIEW_SRC "${TARGET_SRC_PATH}/view/*.cpp")

list(APPEND TARGET_SRC
	${VIEW_SRC}
)

add_library(
    ${TARGET} SHARED
    ${TARGET_SRC}
)

target_link_libraries(
    ${TARGET}
    ${TARGET_LINK_LIBS}
)

set_target_properties(
    ${TARGET} PROPERTIES
        VERSION ${PROJECT_VERSION})

if(BUILD_TESTS)
    include(${CMAKE_MODULE_PATH}/tests/make.cmake)
endif()

if(BUILD_EXAMPLES)
    include(${CMAKE_MODULE_PATH}/examples/build.cmake)
endif()

install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${TARGET_INSTALL_PATH}
    ARCHIVE DESTINATION ${TARGET_INSTALL_PATH}
    PERMISSIONS
        OWNER_WRITE OWNER_READ OWNER_EXECUTE
        GROUP_WRITE GROUP_READ OWNER_EXECUTE
        WORLD_READ
)

add_custom_target(uninstall
    COMMAND "${CMAKE_COMMAND}" -DINSTALL_DIR=${CMAKE_INSTALL_PREFIX} -P
    "${CMAKE_MODULE_PATH}/project/uninstall.cmake")

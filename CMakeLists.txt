cmake_minimum_required(VERSION 2.8.5)

project(sgl)

set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

set(TARGET ${PROJECT_NAME})
set(TARGET_INSTALL_PATH "${CMAKE_INSTALL_PREFIX}/lib")
set(TARGET_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/include")
set(TARGET_SRC_PATH "${CMAKE_SOURCE_DIR}/src")
set(TARGET_LINK_LIBS)

set(FAKEIT_MODULE_PATH "${CMAKE_SOURCE_DIR}/FakeIt")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(LIBRARY_OUTPUT_PATH "lib")

include_directories(${TARGET_INCLUDE_PATH})
include_directories(${FAKEIT_MODULE_PATH}/include)
include_directories(${FAKEIT_MODULE_PATH}/single_header/standalone)

add_compile_options(-std=c++11)
add_compile_options(-Wall)
add_compile_options(-g)

file(GLOB_RECURSE TARGET_SRC "${TARGET_SRC_PATH}/*.cpp")

add_library(${TARGET} SHARED ${TARGET_SRC})
target_link_libraries(${TARGET} ${TARGET_LINK_LIBS})
set_target_properties(${TARGET} PROPERTIES VERSION ${PROJECT_VERSION})

include("${CMAKE_MODULE_PATH}/foreach.cmake")
foreach_include(${TARGET_INCLUDE_PATH} "*.h" "docs/copyright.txt")

if(BUILD_TESTS)
    add_definitions(-DTESTS)
	include(cxxtest)
endif()

if(BUILD_EXAMPLES)
    include(examples)
endif()

if(BUILD_DOCS)
    include(doxygen)
endif()

install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${TARGET_INSTALL_PATH}
    ARCHIVE DESTINATION ${TARGET_INSTALL_PATH}
    PERMISSIONS
        OWNER_WRITE OWNER_READ OWNER_EXECUTE
        GROUP_WRITE GROUP_READ OWNER_EXECUTE
        WORLD_READ)

add_custom_target(uninstall COMMAND "${CMAKE_COMMAND}" -P "${CMAKE_MODULE_PATH}/uninstall.cmake")

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

set(FAKEIT_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/FakeIt")

set(LIBRARY_OUTPUT_PATH "lib")

include_directories(${TARGET_INCLUDE_PATH})
include_directories(${FAKEIT_MODULE_PATH}/include)
include_directories(${FAKEIT_MODULE_PATH}/single_header/standalone)

add_compile_options(-std=c++11)
add_compile_options(-Wall)

file(GLOB_RECURSE TARGET_SRC "${TARGET_SRC_PATH}/*.cpp")

add_library(${TARGET} SHARED ${TARGET_SRC})
target_link_libraries(${TARGET} ${TARGET_LINK_LIBS})
set_target_properties(${TARGET} PROPERTIES VERSION ${PROJECT_VERSION})

if(BUILD_TESTS)
    find_package(CxxTest)
    if(CXXTEST_FOUND)
        include_directories(${CXXTEST_INCLUDE_DIR})
        enable_testing()
        add_definitions(-DTESTS)

        set(CXXTEST_SRC_DIR "tests")
        set(CXXTEST_OUT_DIR "tests")
        set(CXXTEST_GEN_DIR "${CXXTEST_OUT_DIR}/src")
        set(CXXTEST_BIN_DIR "${CXXTEST_OUT_DIR}/bin")

        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${CXXTEST_OUT_DIR}")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${CXXTEST_GEN_DIR}")
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${CXXTEST_BIN_DIR}")

        set(EXECUTABLE_OUTPUT_PATH ${CXXTEST_BIN_DIR})

        file(GLOB src_list "${CXXTEST_SRC_DIR}/*.h")
        foreach(src ${src_list})
            get_filename_component(test_name ${src} NAME_WE)
            set(test_gen_src "${CXXTEST_GEN_DIR}/${test_name}.cpp")
            cxxtest_add_test(${test_name} ${test_gen_src} ${src})
            target_link_libraries(${test_name} ${PROJECT_NAME})
        endforeach()
    endif()
endif()

if(BUILD_EXAMPLES)
    set(EXAMPLES_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/examples")
    set(EXAMPLES_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/examples")

    file(MAKE_DIRECTORY ${EXAMPLES_OUTPUT_DIR})

    file(GLOB EXAMPLES_SUBDIRS_LIST "${EXAMPLES_SOURCE_DIR}/*")
    foreach(EXAMPLE_SUBDIR ${EXAMPLES_SUBDIRS_LIST})
            if(IS_DIRECTORY ${EXAMPLE_SUBDIR})
                    add_subdirectory(${EXAMPLE_SUBDIR})
            endif()
    endforeach()
endif()

install(TARGETS ${TARGET}
    LIBRARY DESTINATION ${TARGET_INSTALL_PATH}
    ARCHIVE DESTINATION ${TARGET_INSTALL_PATH}
    PERMISSIONS
        OWNER_WRITE OWNER_READ OWNER_EXECUTE
        GROUP_WRITE GROUP_READ OWNER_EXECUTE
        WORLD_READ)

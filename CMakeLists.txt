cmake_minimum_required(VERSION 3.23)
project(canbus)

message("canbus_lib Cmake is running")

set(CMAKE_CXX_STANDARD 14)

include_directories(
        include
        include/Vector
)

FILE(GLOB HEADER_FILES
        include/*.h
        include/Vector/*.h
        )

FILE(GLOB SRC_FILES
        include/*.cpp
        include/Vector/*.cpp
        )

add_library(${PROJECT_NAME}_lib
        ${HEADER_FILES}
        ${SRC_FILES}
        )

target_link_libraries(${PROJECT_NAME}_lib)

set_target_properties(${PROJECT_NAME}_lib
        PROPERTIES LINKER_LANGUAGE CXX
        )

message("canbus_lib Cmake is done")

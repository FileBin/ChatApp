cmake_minimum_required(VERSION 3.14)

project(tests LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)


file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

set(PROJECT_SOURCES
    ${SOURCES}
    ${HEADERS}
)

add_executable(tests
  ${PROJECT_SOURCES}
)

include_directories(tests ${LIB_INCLUDE_PATH})

target_link_libraries(tests Networking)
target_link_libraries(tests Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS tests
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

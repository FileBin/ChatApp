cmake_minimum_required(VERSION 3.5)

project(Networking VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIB_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")

add_subdirectory(tests)

set(QT_COMPONENTS Core Network)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS ${QT_COMPONENTS})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS ${QT_COMPONENTS})

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" )
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

set(PROJECT_SOURCES
    ${SOURCES}
    ${HEADERS}
)

add_library(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

include_directories(${PROJECT_NAME} ${LIB_INCLUDE_PATH})

foreach(COMP ${QT_COMPONENTS})
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::${COMP})    
endforeach(COMP ${QT_COMPONENTS})

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

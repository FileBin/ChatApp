cmake_minimum_required(VERSION 3.19)

set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE RESOURCES "${RESOURCES_PATH}/*.*")

set(SERVER_RESOURCES_NAME ServerResources CACHE INTERNAL "")

#copy resources
add_custom_target(${SERVER_RESOURCES_NAME} ALL DEPENDS ${RESOURCES})

add_custom_command(TARGET ${SERVER_RESOURCES_NAME}
    COMMAND ${CMAKE_COMMAND}
        -E copy_directory
        ${RESOURCES_PATH}
        ${CMAKE_CURRENT_BINARY_DIR})

        

cmake_minimum_required(VERSION 3.19)

set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE RESOURCES "${RESOURCES_PATH}/*.*")

set(CLIENT_RESOURCES_NAME ClientResources CACHE INTERNAL "")

#copy resources
add_custom_target(${CLIENT_RESOURCES_NAME} ALL DEPENDS ${RESOURCES})

add_custom_command(TARGET ${CLIENT_RESOURCES_NAME}
    COMMAND ${CMAKE_COMMAND}
        -E copy_directory
        ${RESOURCES_PATH}
        ${CMAKE_CURRENT_BINARY_DIR})

        

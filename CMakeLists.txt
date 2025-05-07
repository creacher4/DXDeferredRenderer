cmake_minimum_required(VERSION 3.20)
project(DXDeferredRenderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# collect src files and create the executable
file(GLOB_RECURSE GRAPHITE_SRC
    CONFIGURE_DEPENDS
    graphite/*.cpp
)

add_executable(graphite WIN32 ${GRAPHITE_SRC})

# include directories
target_include_directories(graphite PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/graphite
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/external/entt/single_include
)

# add external libraries
add_subdirectory(external/assimp)

# global def
target_compile_definitions(graphite PRIVATE
    WIN32_LEAN_AND_MEAN
    UNICODE
    _UNICODE

    # glm cfg
    GLM_FORCE_RADIANS
    GLM_FORCE_DEPTH_ZERO_TO_ONE
    GLM_ENABLE_EXPERIMENTAL
)

# link libraries
target_link_libraries(graphite PRIVATE
    d3d11
    dxgi
    assimp
)

# add stuff in the output directory
# add_custom_command(TARGET graphite POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#         ${CMAKE_CURRENT_SOURCE_DIR}/res $<TARGET_FILE_DIR:graphite>/res
# )

cmake_minimum_required(VERSION 3.22)
include(ExternalProject)
project(VoxPrimEditor VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/lib)

set(GLFW_INSTALL ON)

### Put the names of your source files here ###
set(SRC_FILES 
    main.cpp
    exception.hpp typedefs.hpp
    app.hpp app.cpp
    input.hpp input.cpp
    resource_manager.hpp resource_manager.cpp
    enum_utils.hpp
    string_tools.hpp
)

set(GRAPHICS_SRC_FILES 
    renderer.hpp renderer.cpp
    color.hpp
    vertex_buffer.hpp vertex_buffer.cpp
    vertex_buffer_layout.hpp vertex_buffer_layout.cpp
    index_buffer.hpp index_buffer.cpp
    shader.hpp shader.cpp
    shader_pipeline.hpp shader_pipeline.cpp shader_pipeline.tpp
    primitives.hpp primitives.cpp
    mesh.hpp mesh.cpp
    shaded_mesh.hpp shaded_mesh.cpp
    model.hpp model.cpp
    transform.hpp transform.cpp
    voxel_transform.hpp voxel_transform.cpp
    camera.hpp camera.cpp
    voxel.hpp voxel.cpp
    shader_utils.hpp
)

set(EXTERNAL_SRC_FILES 
    glad.c glad.h
    magic_enum.hpp
)

list(TRANSFORM SRC_FILES PREPEND "src/")
list(TRANSFORM GRAPHICS_SRC_FILES PREPEND "src/graphics/")
list(TRANSFORM EXTERNAL_SRC_FILES PREPEND "src/external/")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${GRAPHICS_SRC_FILES} ${EXTERNAL_SRC_FILES})

ExternalProject_Add(
    glfw_target
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/submodules/glfw
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/lib
)

ExternalProject_Add(
    glm_target
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/submodules/glm
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_SOURCE_DIR}/lib
)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)

### Add link directories here ###
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/lib)

### Add include directories here ###
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src lib/include)

### Uncomment this line if you want the standard libraries to be linked statically ###
# target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)

### Use this line to link external libraries
target_link_libraries(${PROJECT_NAME} glfw3 glm)
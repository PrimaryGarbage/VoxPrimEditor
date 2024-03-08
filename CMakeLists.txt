cmake_minimum_required(VERSION 3.22)
project(VoxPrimEditor VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/lib)

set(GLFW_INSTALL ON)

### Put the names of your source files here ###
set(SRC_FILES 
    main.cpp
)

set(EXTERNAL_SRC_FILES 
    glad.c glad.h
)

list(TRANSFORM SRC_FILES PREPEND "src/")
list(TRANSFORM EXTERNAL_SRC_FILES PREPEND "src/external/")

add_executable(${PROJECT_NAME} ${SRC_FILES} ${EXTERNAL_SRC_FILES})

add_subdirectory(submodules/glfw)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX -d)

### Add link directories here ###
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/lib)

### Add include directories here ###
target_include_directories(${PROJECT_NAME} PRIVATE lib/include)

### Uncomment this line if you want the standard libraries to be linked statically ###
# target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)

### Use this line to link external libraries
target_link_libraries(${PROJECT_NAME} glfw3)
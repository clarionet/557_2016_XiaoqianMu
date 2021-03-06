# Main cmake file

cmake_minimum_required(VERSION 2.6)

# Main project name is ARMaker
project(03_makeshpere)


set(CFILE_PATH  "${CMAKE_SOURCE_DIR}/../SDK/cmake/")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../SDK/cmake/")

message(STATUS "Source directory ${CMAKE_SOURCE_DIR}")
message(STATUS "SDK directory ${CMAKE_SOURCE_DIR}/../SDK")


# Find packages
FIND_PACKAGE(glew REQUIRED)
FIND_PACKAGE(glm REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)


# Include dirs
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW3_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/../gl_common/)

# Add all files to the configuration
file(GLOB 03_makeshpere_SRC  
    main.cpp
    GLBlueSphere.cpp
    GLBlueSphere.h
    GLGreenSphere.cpp
    GLGreenSphere.h
    GLRedSphere.cpp
    GLRedSphere.h
    GLYellowSphere.cpp
    GLYellowShpere.h
    HCI557Common.cpp
    HCI557Common.h
    controls.cpp
    controls.h
    CoordSystem.cpp
    CoordSystem.h
    GLObject.h
    GLObject.cpp
    GLSphere.cpp
    GLSphere.h
    Shaders.h
    Shaders.cpp
    HCI557Datatypes.h
    GLAppearance.h
    GLAppearance.cpp
)

# Create an executable
add_executable(03_makeshpere ${03_makeshpere_SRC})


# Add link directories
# Note required for this project
IF(WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/../SDK/lib)
ELSE(WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/../SDK/lib)
	link_directories(/usr/local/lib)
	link_directories(/usr/local/Cellar/glfw3/3.0.4/lib)
	link_directories(/usr/local/Cellar/glew/1.11.0/lib)
ENDIF(WIN32)


# Add libraries
target_link_libraries(03_makeshpere ${GLEW_LIBRARY} ${GLFW3_LIBRARY} ${OPENGL_LIBRARIES} ${OPENGL_LIBRARIES} )

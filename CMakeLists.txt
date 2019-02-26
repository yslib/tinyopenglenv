# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.3)

project ("OpenGL")

# Handling function-like macros min() and max() defined in windows.h in MSVC
add_definitions(-DNOMINMAX)

#---------------------------------------------------
# Build Type
#---------------------------------------------------
set(CMAKE_CXX_STANDARD 14)

#---------------------------------------------------
# Dependency Module
#---------------------------------------------------
# Compile glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
set(GLFW_DIR "lib/glfw")
add_subdirectory(${GLFW_DIR})
add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

set(_GLFW_INCLUDE_DIR "${GLFW_DIR}/include")								 #glfw headers
set(_GL3W_INCLUDE_DIR "lib/gl3w")											 #gl3w headers
include_directories(${_GLFW_INCLUDE_DIR} ${_GL3W_INCLUDE_DIR})			 

#---------------------------------------------------
# Package Find
#---------------------------------------------------
find_package(OpenGL REQUIRED)
if(OPENGL_FOUND)
	message(STATUS "OpenGL Found:" ${OPENGL_INCLUDE_DIR} ${OPENGL_LIBRARIES})
	include_directories(${OPENGL_INCLUDE_DIR})			#optional
endif(OPENGL_FOUND)

# OpenMP
FIND_PACKAGE(OpenMP)
if(OPENMP_FOUND)
message("OPENMP FOUND")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()



#----------------------------------------------------
# Internal
#----------------------------------------------------

# Set include directories
include_directories("src")


# Set srouce list needed by target
aux_source_directory("src" SRC_LIST)



set(GL3W_LIST "lib/gl3w/GL/gl3w.c")



#---------------------------------------------------
# MRE Module
#---------------------------------------------------


add_executable(
${PROJECT_NAME} 
${SRC_LIST} 
${GL3W_LIST} )
target_link_libraries(${PROJECT_NAME} glfw ${OPENGL_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

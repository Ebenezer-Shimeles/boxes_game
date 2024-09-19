cmake_minimum_required(VERSION 3.10)

project(GRANNY)

add_executable(GRANNY  engine/libs/glad/src/glad.c   
                       engine/render/opengl/shader/shader_program.cc 
                       engine/render/opengl/buffer/vertex_buffer.cc
                       engine/render/opengl/buffer/element_buffer.cc
                       engine/render/opengl/buffer/vertex_array_object.cc
                       main.cc
               )

SET(ENGINE_GLFW_LIB_PATH, "./engine/libs/libglfw3.a")
add_library(ENGINE_GLFW_LIB STATIC IMPORTED )



set_target_properties(ENGINE_GLFW_LIB PROPERTIES IMPORTED_LOCATION "./engine/libs/libglfw3.a")


target_link_libraries(GRANNY  ENGINE_GLFW_LIB gdi32 user32 )


include_directories("./engine/libs/glad/include")
include_directories("./engine/libs")
include_directories("engine")
include_directories("engine/render")
include_directories("engine/render/opengl")
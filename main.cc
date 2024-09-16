#include <glad/glad.h>

#include <iostream>
#include <cstring>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#ifndef GL_CALL
#define GL_CALL(x) x;\
{\
    bool is_gl_error = false; \
    while(GLenum y = glGetError()) { \
        if (y == GL_NO_ERROR) break; \
        is_gl_error = true; \
        std::cout << "OpenGL Error: " << y << '\n'; \
    } \
    if (is_gl_error) {\
        exit(1);\
    }\
}
#endif

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}


int main(){
   if(!glfwInit()){
      std::cerr << "Error could not init glfw!\n";
      return -1;
   }
   
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  

   auto window = glfwCreateWindow(800, 800, "Granny", nullptr, nullptr);
   if(!window){
     std::cerr << "Error could not create window!";
     glfwTerminate();
     return -1;
   }
   
   glfwMakeContextCurrent(window);
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cerr << "Failed to initialize GLAD" << std::endl;
      glfwTerminate();
      return -1;
      
   }   
   GL_CALL(glEnable(GL_DEPTH_TEST));
 
   

   char*   vertextShaderSrc = "#version 330 core\n"\
                               "layout(location=0) in vec2 pos;"
                               "void main(){"\
                               "   gl_Position = vec4(pos,0,1.0);"\
                               "}";
                               ;
   uint32_t vertexshader = glCreateShader(GL_VERTEX_SHADER);
   GL_CALL(glShaderSource(vertexshader, 1,&vertextShaderSrc, (GLint*)nullptr));
   GL_CALL(glCompileShader(vertexshader));
   int32_t compileStatus;
   glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &compileStatus);
   if(!compileStatus){
      char erro[255]{};
      glGetShaderInfoLog(vertexshader, 255, &compileStatus, erro);
      std::cout << "Couldn't compile vertex shader!: " << erro <<'\n';
      return -1;
   }
   //

   const char* fragmentShaderSource = "#version 330 core\n"\
                                      "out vec4 FragColor;\n"\
                                      "void main(){\n"\
                                      "  FragColor = vec4(1.0, 1.0, 0.0, 0.6);"
                                      "}"   
   ;
   GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, (GLint*)nullptr);
   glCompileShader(fragmentShader);
   
   int32_t frcompileStatus;
   glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &frcompileStatus);
   if(!frcompileStatus){
      char erro[255]{};
      glGetShaderInfoLog(fragmentShader, 255, &frcompileStatus, erro);
      std::cout << "Couldn't compile fragment shader!: " << erro <<'\n';
      return -1;
   }
   //
   GLuint program = glCreateProgram();
   glAttachShader(program, vertexshader);
   glAttachShader(program, fragmentShader);
   glLinkProgram(program);
   GLint linkStatus;
   glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
   if(!linkStatus){
    char infoLog[255]{};
     glGetProgramInfoLog(program, 255, nullptr, infoLog);
     std::cerr << "Unable to link program! " << infoLog << '\n';
     return -1;

   }
   GL_CALL(glUseProgram(program));
   //
   float vertices[] = {
     1.0, -1.0,
     -1.0, -1.0,
     -1.0, 1.0
   };
   uint32_t VAO;
   GL_CALL(glGenVertexArrays(1, &VAO));
   GL_CALL(glBindVertexArray(VAO)); 


   uint32_t VBO;
   GL_CALL(glGenBuffers(1, &VBO));
   GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
   GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertices, GL_STATIC_DRAW));
   
   GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 2 *sizeof(float),nullptr));
   
  
   while(!glfwWindowShouldClose(window)){
       GL_CALL(glClearColor(0, 0, 0, 0));
       GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
       //
       GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
       GL_CALL(glEnableVertexAttribArray(0));
       GL_CALL(glUseProgram(program));
       GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
    
       //
       glfwPollEvents();
       glfwSwapBuffers(window);
   }
   glfwDestroyWindow(window);
   glfwTerminate();
}
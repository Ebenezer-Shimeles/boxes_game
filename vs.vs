#version 330 core
layout(location=0) in vec2 pos;
layout(location=1) in vec2 textPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 tPos;
void main(){
   
   gl_Position = projection* view*model * vec4(pos,-1.0,1.0);
   tPos = textPos;
}
 
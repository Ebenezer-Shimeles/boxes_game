#include <glad/glad.h>
#include <cstdio>
#define GL_CALL(exp) exp; gl_check_error(__LINE__);

inline void gl_check_error(size_t line) {
    bool flag = false;
    GLint err;
    while( (err = glGetError()) != GL_NO_ERROR){
        printf( "Opengl error %i   on line %i\n", err, line);
    }
    if(flag){
        exit(-1);
    }
}
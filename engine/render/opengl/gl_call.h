#ifndef GL_CALL
#include <cstdio>
#include <cstdlib>
#define GL_CALL(x) x;\
{\
    bool is_gl_error = false; \
    while(GLenum y = glGetError()) { \
        if (y == GL_NO_ERROR) break; \
        is_gl_error = true; \    
        fprintf(stderr, "OPENGL ERROR: %i", y); \
    } \
    if (is_gl_error) {\
        exit(1);\
    }\
}
#endif

#ifndef __OPENGL_UTILS_HPP__
#define __OPENGL_UTILS_HPP__

#include "logger.hpp"

#define glCall(code) while(glGetError() != GL_NO_ERROR); code; while(GLenum error = glGetError())\
    Logger::inst().logError("OpenGL error: {0}. File: {1}, line: {2}", error, __FILE__, __LINE__)

#endif // __OPENGL_UTILS_HPP__
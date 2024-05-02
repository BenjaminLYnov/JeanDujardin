#include "Shader.h"

#include <stdexcept>
#include <GL/glew.h>

#include <iostream>
#include <sstream>
#include <fstream>

namespace {
    std::string readShader(const char* filename)
    {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open())
            throw std::runtime_error("Could not open shader");

        std::stringstream buffer;
        buffer << inputFile.rdbuf();

        inputFile.close();

        return buffer.str();
    }
}

unsigned int Shader::loadShaders(ShaderInfo* shaderInfo)
{
    if (shaderInfo == nullptr)
        throw std::runtime_error("Null pointer in loadShaders");

    auto program = glCreateProgram();
    auto* entry = shaderInfo;

    while (entry->type != GL_NONE) {
        auto shaderId = glCreateShader(entry->type);
        entry->shaderID = shaderId;

        auto str = readShader(entry->filename);
        const char* strData = str.c_str();

        glShaderSource(shaderId, 1, &strData, nullptr);
        glCompileShader(shaderId);

        GLint hasCompiled;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &hasCompiled);

        if (!hasCompiled) {
            GLint infoLogSize;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogSize);

            GLchar* logBuffer = new GLchar[infoLogSize + 1];

            glGetShaderInfoLog(shaderId, infoLogSize, &infoLogSize, logBuffer);

            std::cerr << logBuffer << std::endl;

            delete[] logBuffer;

            throw std::runtime_error("Could not compile shader");
        }

        glAttachShader(program, shaderId);
        ++entry;
    }

    glLinkProgram(program);

    GLint hasLinked;
    glGetProgramiv(program, GL_LINK_STATUS, &hasLinked);

    if (!hasLinked) {
        GLint infoLogSize;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogSize);

        GLchar* logBuffer = new GLchar[infoLogSize + 1];

        glGetProgramInfoLog(program, infoLogSize, &infoLogSize, logBuffer);

        std::cerr << logBuffer << std::endl;

        delete[] logBuffer;

        throw std::runtime_error("Could not link program");
    }

    return program;
}

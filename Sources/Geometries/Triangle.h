#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shader/Shader.h"
#include "lib/Math/Vertex.h"

#include <GL/glew.h>
#include <array>

template<typename T>
class Mat4;

template<typename T>
struct Triangle 
{
    using vertex_type = Vertex<T>;

    Triangle(const vertex_type& p0, const vertex_type& p1, const vertex_type& p2) 
        : m_points{ {p0, p1, p2} }
        , m_vao(0)
        , m_vbo(0)
        , m_program(0)
    {
        load();
    }

    ~Triangle() {}

    void load()
    {
        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(m_points), m_points.data(), GL_STATIC_DRAW);

        ShaderInfo shaders[] = {
            {GL_VERTEX_SHADER, "ressources/triangle.vert"},
            {GL_FRAGMENT_SHADER, "ressources/triangle.frag"},
            {GL_NONE, nullptr}
        };

        m_program = Shader::loadShaders(shaders);

        glUseProgram(m_program);

        // only works for T = float :shrug:
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::position) * 2);
        glEnableVertexAttribArray(2);
    }

    void render(const Mat4<T>& MVP) 
    {
        glBindVertexArray(m_vao);

        GLuint mvpLocation = glGetUniformLocation(m_program, "MVP");
        glUniformMatrix4fv(mvpLocation, 1, 0, MVP.data());

        glDrawArrays(GL_TRIANGLES, 0, int(m_points.size()));
    }

private:
    std::array<vertex_type, 3> m_points;
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_program;
};

using TriangleF = Triangle<float>;

#endif // TRIANGLE_H